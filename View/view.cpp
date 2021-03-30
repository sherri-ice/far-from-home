#include "view.h"
#include "Model/constants.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <utility>
#include <vector>

View::View(AbstractController* controller,
           std::shared_ptr<Model> model)
    : controller_(controller),
      model_(std::move(model)) {
  setWindowTitle(constants::kApplicationName);
  setMinimumSize(960, 540);
  resizer_.ChangeSystem(width(), height());
  show();

  time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
  view_timer_.start();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  DrawGameObjects(&painter);
  // DrawMap(&painter);
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
  if (event->key() == Qt::Key_Up) {
    pressed_keys_[Qt::Key_Up] = true;
  }
  if (event->key() == Qt::Key_Down) {
    pressed_keys_[Qt::Key_Down] = true;
  }
  if (event->key() == Qt::Key_Left) {
    pressed_keys_[Qt::Key_Left] = true;
  }
  if (event->key() == Qt::Key_Right) {
    pressed_keys_[Qt::Key_Right] = true;
  }
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
  if (event->key() == Qt::Key_Up) {
    pressed_keys_[Qt::Key_Up] = false;
  }
  if (event->key() == Qt::Key_Down) {
    pressed_keys_[Qt::Key_Down] = false;
  }
  if (event->key() == Qt::Key_Left) {
    pressed_keys_[Qt::Key_Left] = false;
  }
  if (event->key() == Qt::Key_Right) {
    pressed_keys_[Qt::Key_Right] = false;
  }
}

void View::DrawMap(QPainter* painter) {
  painter->setBrush(Qt::red);
  painter->setBackground(Qt::red);
}

void View::DrawGameObjects(QPainter* painter) {
  std::vector<std::shared_ptr<GameObject>>
      drawable_objects = model_->GetDrawableGameObjects();
  for (const auto& object : drawable_objects) {
    object->Draw(painter);
  }
}

void View::Resize() {
  resizer_.ChangeSystem(width(), height());
  controller_->RescaleObjects(resizer_);
}

void View::resizeEvent(QResizeEvent*) {
  Resize();
}
