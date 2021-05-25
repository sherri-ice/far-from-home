#include <algorithm>

#include "resizer.h"

void Resizer::ChangeSystem(double window_width, double window_height) {
  game_size_.SetWidth(window_width);
  game_size_.SetHeight(window_height);
}

Point Resizer::WindowToGameCoordinate(const Point& window_coordinate) const {
  return Point(window_coordinate - origin_offset_) * scaling_coefficient_;
}

Point Resizer::GameToWindowCoordinate(const Point& game_coordinate) const {
  return Point(game_coordinate / scaling_coefficient_ + origin_offset_);
}

Size Resizer::GetGameSize() const {
  return game_size_;
}

Size Resizer::GameToWindowSize(const Size& size) const {
  return Size(size / scaling_coefficient_);
}

void Resizer::Update(double radius, const Point& position) {
  scaling_coefficient_ =
      radius / std::min(game_size_.GetWidth(), game_size_.GetHeight());
  auto pos_size = Size(position.GetX(), position.GetY());
  origin_offset_ = pos_size / scaling_coefficient_ * -1 + game_size_ / 2;
}

double Resizer::GameToWindowLength(double length) const {
  return length / scaling_coefficient_;
}
