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

  QRect inner_rect = QRect(static_cast<int>(width_shift_),
                           static_cast<int>(height_shift_),
                           static_cast<int>(inner_width_),
                          static_cast<int>(inner_height_));
  QRect inner_small_rect = QRect(static_cast<int>(width_shift_),
                                 static_cast<int>(height_shift_),
                                 static_cast<int>(inner_width_),
                                 static_cast<int>(inner_small_height_));
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

  painter->drawPixmap(0, 0, static_cast<int>(size_.GetWidth()),
                      static_cast<int>(size_.GetHeight()), skin_);
  painter->restore();
}

void GlobalProgressBar::SetMaxValue(int max_value) {
  max_value_ = max_value;
}

void GlobalProgressBar::SetSkin(const QPixmap& skin) {
  skin_ = skin;
}

void GlobalProgressBar::UpdateSize(Resizer* resizer, int new_parameter) {
  position_ = Point(resizer->ResizeLength(position_.GetX(),
                                          new_parameter),
                    resizer->ResizeLength(position_.GetY(),
                                          new_parameter));
  size_ = Size(resizer->ResizeLength(size_.GetWidth(), new_parameter),
               resizer->ResizeLength(size_
                                         .GetHeight(),
                                     new_parameter));
  inner_width_ = size_.GetWidth() * constants::kGetInnerWidthCoeff;
  inner_height_ = size_.GetHeight() * constants::kGetInnerHeightCoeff;
  inner_small_height_ =
      size_.GetHeight() * constants::kGetInnerSmallHeightCoeff;
  width_shift_ = size_.GetWidth() * constants::kGetWidthShiftCoeff;
  height_shift_ = size_.GetHeight() * constants::kGetHeightShiftCoeff;
}
