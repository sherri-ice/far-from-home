#include "resizer.h"
#include <algorithm>

void Resizer::ChangeSystem(double window_width, double window_height) {
  scaling_coefficient_ = std::max(game_size_.GetWidth() / window_width,
                                  game_size_.GetHeight() / window_height);
  Size real_size(game_size_.GetWidth() / scaling_coefficient_,
                 game_size_.GetHeight() / scaling_coefficient_);
  origin_offset_.SetWidth((window_width - real_size.GetWidth()));
  origin_offset_.SetHeight((window_height - real_size.GetHeight()));
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
  auto t = size / scaling_coefficient_;
  return size / scaling_coefficient_;
}

