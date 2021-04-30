#ifndef GAMEOBJECT_FOOD_H_
#define GAMEOBJECT_FOOD_H_

#include "game_object.h"

class Food : public GameObject {
 public:
  Food(const Size& size, const Point& position);
  ~Food() override = default;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;

};

#endif  // GAMEOBJECT_FOOD_H_
