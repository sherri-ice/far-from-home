#include "view.h"
#include "../Model/constants.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <utility>
#include <vector>
#include <algorithm>

View::View(AbstractController* controller,
           std::shared_ptr<Model> model)
    : controller_(controller),
      model_(std::move(model)) {
  setWindowTitle(constants::kApplicationName);
  resize(constants::kGameWidth, constants::kGameHeight);
  resizer_.ChangeSystem(width(), height());
  controller->StartGame();
  show();

  time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
  view_timer_.start();

}

void View::paintEvent(QPaintEvent*) {

    QPainter painter(this);

  DrawGameObjects(&painter);
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_) {
    int delta_time = time_between_ticks_.elapsed();
    time_between_ticks_.restart();
    controller_->Tick(controller_->GetCurrentTime() + delta_time);
  }
  repaint();
}

void View::keyPressEvent(QKeyEvent* event) {
  pressed_keys_[event->key()] = true;
}

Size View::GetPlayerVelocity() {
  if (pressed_keys_[Qt::Key_Up]) {
    player_velocity_ += Size(0, -100);
  }
  if (pressed_keys_[Qt::Key_Down]) {
    player_velocity_ += Size(0, 100);
  }
  if (pressed_keys_[Qt::Key_Left]) {
    player_velocity_ += Size(-100, 0);
  }
  if (pressed_keys_[Qt::Key_Right]) {
    player_velocity_ += Size(100, 0);
  }
  return player_velocity_;
}

void View::ClearVelocity() {
  player_velocity_ = Size(0, 0);
}

void View::keyReleaseEvent(QKeyEvent* event) {
  pressed_keys_[event->key()] = false;
}

void View::DrawGameObjects(QPainter* painter) {

    controller_->GetPlayer()->GetViewCircle().Draw(painter, &resizer_);

    std::vector<std::shared_ptr<GameObject>>
      drawable_objects = model_->GetDrawableGameObjects();

    for (const auto& object : drawable_objects) {
    object->Draw(painter, &resizer_);
  }
}

void View::Resize() {
  resizer_.ChangeSystem(width(), height());
}

void View::resizeEvent(QResizeEvent*) {
  Resize();
}

void View::UpdateResizer(double radius, const Point& position) {
  resizer_.Update(radius, position);
}

double View::GetViewSize() {
  auto radius = model_->GetPlayer()->GetViewCircle().GetWantedRadius();
  if (pressed_keys_[Qt::Key_E]) {
    radius += constants::kResizerScale;
  }
  if (pressed_keys_[Qt::Key_Q]) {
    radius -= constants::kResizerScale;
  }
  radius = std::min(std::max(radius, constants::kViewCircleMin),
                    constants::kViewCircleMax);
  return radius;
}
