#include "food.h"

std::mt19937 Food::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

Food::Food(const Size& size, const Point& position) : GameObject(size,
                                                                 position) {
  std::uniform_int_distribution<> quality
  (constants::kMinQualityForGeneration, constants::kMaxQuality);
  std::uniform_real_distribution<> speed(constants::kMinDecaySpeed,
                                         constants::kMaxDecaySpeed);
  food_quality_ = quality(random_generator_);
  decay_speed_ = speed(random_generator_);
}

void Food::Draw(QPainter* painter, Resizer* resizer) const {
    rigid_body_.Draw(painter, resizer);
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
  painter->translate(position.GetX(), position.GetY());
  int width = static_cast<int>(size.GetWidth());
  int height = static_cast<int>(size.GetHeight());
  painter->drawPixmap(-width / 2, -height / 2, width, height, skin_);
  painter->restore();
}

void Food::Tick(int delta_time) {
  food_quality_ -= decay_speed_;
  if (food_quality_ < constants::kMinQuality + constants::kEpsilon) {
    is_dead_ = true;
  }
}

double Food::GetFoodQuality() const {
  return food_quality_;
}
