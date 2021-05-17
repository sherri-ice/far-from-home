#include <algorithm>

#include <QKeyEvent>
#include <QGraphicsScene>
#include <utility>
#include <vector>

#include "../GameObject/portal_object.h"
#include "../Model/constants.h"
#include "progress_bar.h"
#include "view.h"


View::View(AbstractController* controller,
           std::shared_ptr<Model> model)
    : controller_(controller),
      model_(std::move(model)) {
  setWindowTitle(constants::kApplicationName);
  resize(constants::kGameWidth, constants::kGameHeight);
  resizer_.ChangeSystem(width(), height());
  controller->StartGame();
  show();
  setStyleSheet("background-color: #32CD32");

  time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
  view_timer_.start();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);

  DrawGameObjects(&painter);
  DrawWarnings(&painter);
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
    player_velocity_ += Size(0, -1);
  }
  if (pressed_keys_[Qt::Key_Down]) {
    player_velocity_ += Size(0, 1);
  }
  if (pressed_keys_[Qt::Key_Left]) {
    player_velocity_ += Size(-1, 0);
  }
  if (pressed_keys_[Qt::Key_Right]) {
    player_velocity_ += Size(1, 0);
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
  controller_->GetPlayer()->GetCatGroup().Draw(painter, &resizer_);
  std::vector<std::shared_ptr<GameObject>>
      drawable_objects = model_->GetDrawableGameObjects();
  for (const auto& object : drawable_objects) {
    if (IsOnTheScreen(object)) {
      object->Draw(painter, &resizer_);
    }
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

void View::mousePressEvent(QMouseEvent* event) {
  Point point = Point(event->x(), event->y());
  auto needed = resizer_.WindowToGameCoordinate(point);
  controller_->ScanIfObjectWereClicked(needed);
}

Point View::GetCoordinatesForWarning() const {
  return Point(width() / 2, 0);
}

bool View::IsOnTheScreen(const std::shared_ptr<GameObject>& object) {
  auto object_pos = object->GetDrawPosition();
  auto screen_rect = this->rect();
  double height_shift = screen_rect.height() * constants::kFactorForScreen;
  double width_shift = screen_rect.width() * constants::kFactorForScreen;
  Point top_point = Point(screen_rect.topLeft().x() - width_shift,
                          screen_rect.topLeft().y() - height_shift);
  auto game_top_point = resizer_.WindowToGameCoordinate(top_point);
  Point bottom_point =
      Point(screen_rect.bottomRight().x() + width_shift, screen_rect
      .bottomRight().y() + height_shift);
  auto game_bottom_point = resizer_.WindowToGameCoordinate(bottom_point);

  if (object_pos.GetX() < game_top_point.GetX()
      || object_pos.GetX() > game_bottom_point.GetX()) {
    return false;
  }
  if (object_pos.GetY() < game_top_point.GetY()
      || object_pos.GetY() > game_bottom_point.GetY()) {
    return false;
  }
  return true;
}

void View::DrawWarnings(QPainter* painter) {
  for (const auto& warning : model_->GetWarnings()) {
    warning->Draw(painter, &resizer_);
  }
}
