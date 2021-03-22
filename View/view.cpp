#include "view.h"
#include <QDebug>
#include <QKeyEvent>
#include <Model/constants.h>

View::View(AbstractController* controller) : controller_(controller),
  player_velocity_(0, 0) {
  show();
  setMinimumSize(500, 500);
  controller_->SetPlayerPosition(Point(230, 230));

  time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
  view_timer_.start();

  ClearPressedKeys();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  controller_->GetPlayer()->Draw(&painter);
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_) {
    int delta_time = time_between_ticks_.elapsed();
    time_between_ticks_.restart();
    controller_->Tick(controller_->GetCurrentTime() + delta_time);
  } else {
    controller_->Tick(controller_->GetCurrentTime() +
    constants::kTimeOfPlayerMove);
  }
  repaint();
}

void View::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Up) {
    pressed_keys_[Qt::Key_Up] = true;
    player_move_timer_.start(constants::kTimeOfPlayerMove);
  }
  if (event->key() == Qt::Key_Down) {
    pressed_keys_[Qt::Key_Down] = true;
    player_move_timer_.start(constants::kTimeOfPlayerMove);
  }
  if (event->key() == Qt::Key_Left) {
    pressed_keys_[Qt::Key_Left] = true;
    player_move_timer_.start(constants::kTimeOfPlayerMove);
  }
  if (event->key() == Qt::Key_Right) {
    pressed_keys_[Qt::Key_Right] = true;
    player_move_timer_.start(constants::kTimeOfPlayerMove);
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

void View::ClearPressedKeys() {
  pressed_keys_[Qt::Key_Up] = false;
  pressed_keys_[Qt::Key_Down] = false;
  pressed_keys_[Qt::Key_Left] = false;
  pressed_keys_[Qt::Key_Right] = false;
}

void View::keyReleaseEvent(QKeyEvent* event) {
  player_move_timer_.stop();
  ClearPressedKeys();
}
