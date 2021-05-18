#include "global_progress_bar.h"

GlobalProgressBar::GlobalProgressBar(int max_value,
                                     int current_value,
                                     const Point& position,
                                     const Size& size) : max_value_(max_value),
                                                         current_value_
                                                         (current_value),
                                                         position_(position),
                                                         size_(size) {
}

void GlobalProgressBar::UpdateCurrentValue(int new_value) {
  current_value_ = new_value;
}

void GlobalProgressBar::Draw(QPainter* painter) const {
  painter->save();
  painter->translate(position_.GetX(), position_.GetY());

  QRect inner_rect = QRect(width_shift_, height_shift_, inner_width_,
                          inner_height_);
  QRect inner_small_rect = QRect(width_shift_, height_shift_, inner_width_,
                                 inner_small_height_);
  painter->setBrush(QBrush(blue_));
  painter->setPen(QPen(blue_));
  painter->drawRect(inner_rect);

  painter->setBrush(QBrush(light_blue_));
  painter->setPen(QPen(light_blue_));
  painter->drawRect(inner_small_rect);

  int rect_width = current_value_ * inner_width_ / max_value_;
  if (current_value_ < 0) {
    rect_width = 0;
  }
  inner_rect.setWidth(rect_width);
  inner_small_rect.setWidth(rect_width);

  if (current_value_ < max_value_ * constants::kSevereHungerPercent) {
    painter->setBrush(red_);
    painter->drawRect(inner_rect);
    painter->setBrush(light_red_);
    painter->setPen(light_red_);
    painter->drawRect(inner_small_rect);
  } else if (current_value_ < max_value_ * constants::kMediumHungerPercent) {
    painter->setBrush(QBrush(orange_));
    painter->drawRect(inner_rect);
    painter->setBrush(light_orange_);
    painter->setPen(light_orange_);
    painter->drawRect(inner_small_rect);
  } else {
    painter->setBrush(green_);
    painter->drawRect(inner_rect);
    painter->setBrush(light_green);
    painter->setPen(light_green);
    painter->drawRect(inner_small_rect);
  }

  painter->drawPixmap(0, 0, size_.GetWidth(), size_.GetHeight(), skin_);
  painter->restore();
}

void GlobalProgressBar::SetMaxValue(int max_value) {
  max_value_ = max_value;
}

void GlobalProgressBar::SetSkin(const QPixmap& skin) {
  skin_ = skin;
}
