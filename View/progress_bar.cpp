#include "progress_bar.h"

ProgressBar::ProgressBar(const Point& center) {
  this->setWidth(progress_bar_constants::kWidth);
  this->setHeight(progress_bar_constants::kHeight);
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

void ProgressBar::IncCurrentValue(int delta_time) {
  cur_value_ += delta_time;
  if (cur_value_ > max_value_) {
    cur_value_ = max_value_;
  }
}

void ProgressBar::Draw(QPainter* painter, Resizer* resizer) const {
  if (is_visible_) {
    painter->save();
    auto rect = *this;
    auto game_size = Size(rect.width(), rect.height());
    auto window_size = resizer->GameToWindowSize(game_size);
    auto game_coordinate = Point(rect.x(), rect.y() -
    progress_bar_constants::kOffset);
    auto window_coordinates = resizer->GameToWindowCoordinate(game_coordinate);
    rect.setX(window_coordinates.GetX());
    rect.setY(window_coordinates.GetY());
    rect.setWidth(window_size.GetWidth());
    rect.setHeight(window_size.GetHeight());

    QRect inner_rect = QRect(rect.x() + rect.width() *
        progress_bar_constants::kGetWidthShiftCoeff, rect.y() + rect.height()
        * progress_bar_constants::kGetHeightShiftCoeff, rect.width() *
        progress_bar_constants::kGetInnerWidthCoeff, rect.height() *
        progress_bar_constants::kGetInnerHeightCoeff);
    QRect inner_small_rect = inner_rect;
    inner_small_rect.setHeight(rect.height() *
    progress_bar_constants::kGetInnerSmallHeightCoeff);

    painter->setBrush(QBrush(blue_));
    painter->setPen(QPen(blue_));
    painter->drawRect(inner_rect);
    painter->setBrush(QBrush(light_blue_));
    painter->setPen(QPen(light_blue_));
    painter->drawRect(inner_small_rect);

    double inner_width = static_cast<double>(inner_rect.width()) * cur_value_ /
        max_value_;

    inner_rect.setWidth(inner_width);
    inner_small_rect.setWidth(inner_width);

    painter->setBrush(QBrush(pink_));
    painter->setPen(QPen(pink_));
    painter->drawRect(inner_rect);
    painter->setBrush(QBrush(light_pink_));
    painter->setPen(QPen(light_pink_));
    painter->drawRect(inner_small_rect);

    painter->drawPixmap(rect.x(), rect.y(), rect.width(), rect.height(), skin_);
    painter->restore();
  }
}

void ProgressBar::SetVisible() {
  is_visible_ = true;
}

void ProgressBar::SetInvisible() {
  is_visible_ = false;
}
