#include "view.h"
#include <QDebug>
#include <QKeyEvent>
#include <Model/constants.h>

View::View(AbstractController* controller) : controller_(controller) {
  show();
  setMinimumSize(500, 500);
  time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
  view_timer_.start();
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  auto current_cat = controller_->GetCat();
  current_cat->Draw(&painter);
}

void View::keyPressEvent(QKeyEvent* event) {
  auto current_cat = controller_->GetCat();
  if (event->key() == Qt::Key_Up) {
    current_cat->Move(static_cast<int>(Directions::kUp));
  } else if (event->key() == Qt::Key_Right) {
    current_cat->Move(static_cast<int>(Directions::kRight));
  } else if (event->key() == Qt::Key_Left) {
    current_cat->Move(static_cast<int>(Directions::kLeft));
  } else if (event->key() == Qt::Key_Down) {
    current_cat->Move(static_cast<int>(Directions::kDown));
  }
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_) {
    repaint();
  }
  // int delta_time = time_between_ticks_.elapsed();
  time_between_ticks_.restart();
  // controller_->Tick(controller_->GetCurrentTime() + delta_time);
}
