#include "progress_bar.h"

#include <iostream>

#include <QDebug>

ProgressBar::ProgressBar(const Point& center, const Size& size) {
  center_ = center;
  this->setWidth(constants::kWidth);
  this->setHeight(constants::kHeight);
  QPoint top_left = QPoint(center.GetX() - this->width() / 2,
                              center.GetY() - this->height() / 2);
  QPoint bottom_right = QPoint(center.GetX() + this->width() / 2,
                               center.GetY() + this->height() / 2);
  this->setTopLeft(top_left);
  this->setBottomRight(bottom_right);
}

void ProgressBar::SetRange(int min_value, int max_value) {
  min_value_ = min_value;
  cur_value_ = min_value;
  max_value_ = max_value;
}

void ProgressBar::IncCurrentValue() {
  if (cur_value_ >= max_value_) {
    return;
  }
    cur_value_ += (max_value_ - min_value_) / time_to_be_full_;
    // qDebug() << cur_value_;
}

bool ProgressBar::IsFull() {
  return (cur_value_ < max_value_);
}

void ProgressBar::Draw(QPainter* painter, Resizer* resizer) const {
  if (is_visible_) {
    painter->save();
    auto rect = *this;
    auto game_size = Size(rect.width(), rect.height());
    auto window_size = resizer->GameToWindowSize(game_size);
    auto game_coordinate = Point(rect.x(), rect.y() - constants::kOffset);
    auto window_coordinates = resizer->GameToWindowCoordinate(game_coordinate);
    rect.setX(window_coordinates.GetX());
    rect.setY(window_coordinates.GetY());
    rect.setWidth(window_size.GetWidth());
    rect.setHeight(window_size.GetHeight());

    double
        width = static_cast<double>(rect.width()) / (max_value_ - min_value_) * 100;
    QRect inner_rect(window_coordinates.GetX(),
                     window_coordinates.GetY(),
                     width * cur_value_,
                     rect.height());
    painter->drawRect(rect);
    painter->fillRect(inner_rect, Qt::yellow);
    painter->drawRect(inner_rect);
    painter->restore();
  }
}

void ProgressBar::SetVisible() {
  is_visible_ = true;
}

void ProgressBar::SetInvisible() {
  is_visible_ = false;
}

void ProgressBar::SetTimeToBeFull(int time_to_be_full) {
  time_to_be_full_ = time_to_be_full;
}

