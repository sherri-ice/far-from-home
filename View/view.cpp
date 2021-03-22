#include "view.h"
#include <QDebug>
#include <QKeyEvent>
#include <Model/constants.h>
#include <QGraphicsScene>
#include <iostream>

View::View(AbstractController* controller) : controller_(controller),
  player_velocity_(0, 0) {
  setWindowTitle(constants::kApplicationName);
  setMinimumSize(960, 540);
  show();
  controller_->SetPlayerPosition(Point(230, 230));

  // time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
  // view_timer_.start();

  ClearPressedKeys();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  controller_->GetPlayer()->Draw(&painter);
  // DrawMap(&painter);
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_) {
    int delta_time = time_between_ticks_.elapsed();
    time_between_ticks_.restart();
    controller_->Tick(controller_->GetCurrentTime() + delta_time);
  } else {
    controller_->Tick(controller_->GetCurrentTime());
  }
  repaint();
}

void View::keyPressEvent(QKeyEvent* event) {
  std::cout << "You're pressing " << event->key() << std::endl;
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

void View::ClearPressedKeys() {
  pressed_keys_[Qt::Key_Up] = false;
  pressed_keys_[Qt::Key_Down] = false;
  pressed_keys_[Qt::Key_Left] = false;
  pressed_keys_[Qt::Key_Right] = false;
}

void View::keyReleaseEvent(QKeyEvent* event) {
  std::cout << "You're releasing " << event->key() << std::endl;
  ClearPressedKeys();
}

void View::DrawMap(QPainter* painter) {
  painter->setBrush(Qt::red);
  painter->setBackground(Qt::red);
}

