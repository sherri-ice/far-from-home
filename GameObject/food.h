#ifndef GAMEOBJECT_FOOD_H_
#define GAMEOBJECT_FOOD_H_

#include "game_object.h"

class Food : public GameObject {
 public:
  Food();
  ~Food() override = default;

  void Draw(QPainter* painter) const override;
  void Tick(int time) override;

 private:
  int meal_;
};

#endif  // GAMEOBJECT_FOOD_H_
