#include "progress_bar.h"

#include <iostream>

ProgressBar::ProgressBar(const Point& center, const Size& size) {
  center_ = center;
  this->setWidth(150);
  this->setHeight(10);
}

void ProgressBar::SetRange(int min_value, int max_value) {
  min_value_ = min_value;
  cur_value_ = min_value;
  max_value_ = max_value;
}

void ProgressBar::IncCurrentValue() {
  ++cur_value_;
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
    auto game_coordinate = Point(rect.x(), rect.y() - constants::offset);
    auto window_coordinates = resizer->GameToWindowCoordinate(game_coordinate);
    rect.setX(window_coordinates.GetX() - window_size.GetWidth() / 2);
    rect.setY(window_coordinates.GetY());
    rect.setWidth(window_size.GetWidth());
    rect.setHeight(window_size.GetHeight());

    double
        width = static_cast<double>(rect.width()) / (max_value_ - min_value_);
    QRect inner_rect(window_coordinates.GetX() - window_size.GetWidth() / 2,
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

