#include "warning.h"

void Warning::Draw(QPainter* painter, Resizer* resizer) const {
  if (is_visible_) {
    painter->save();
    auto rect = rect_;
    auto game_size = Size(rect.width(), rect.height());
    auto window_size = resizer->GameToWindowSize(game_size);
    auto game_coordinate = Point(rect.x(), rect.y()  - warning_constants::offset);
    auto window_coordinates = resizer->GameToWindowCoordinate(game_coordinate);
    rect.setX(window_coordinates.GetX() - window_size.GetWidth() / 2);
    rect.setY(window_coordinates.GetY() - window_size.GetHeight() / 2);
    rect.setWidth(window_size.GetWidth());
    rect.setHeight(window_size.GetHeight());
    painter->drawRect(rect);
    painter->restore();
  }
}

Warning::Warning(const Point& center) {
  rect_ = QRect(center.GetX(), center.GetY(), 10, 10);
}

void Warning::SetVisible() {
  is_visible_ = true;
}

void Warning::SetInvisible() {
  is_visible_ = false;
}
