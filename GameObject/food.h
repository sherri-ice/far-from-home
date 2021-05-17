#ifndef GAMEOBJECT_FOOD_H_
#define GAMEOBJECT_FOOD_H_

#include <random>

#include "game_object.h"

namespace constants {
const int kMaxQuality = 50;
const int kMinQuality = -50;
const int kMinQualityForGeneration = -10;
const double kMaxDecaySpeed = 0.05;
const double kMinDecaySpeed = 0.001;
}  // namespace constants

class Food : public GameObject {
 public:
  Food(const Size& size, const Point& position);
  ~Food() override = default;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int delta_time) override;

  double GetFoodQuality() const;

 private:
  double food_quality_;
  double decay_speed_;

  static std::mt19937 random_generator_;
};
#endif  // GAMEOBJECT_FOOD_H_
