#ifndef FOOD_H
#define FOOD_H

#include "game_object.h"

class Food : public GameObject {
 public:
  explicit Food();
  ~Food() override = default;

  void Draw(QPainter* painter) const override;
  void Tick(int time) override;

 private:
  int meal_;
};

#endif //FOOD_H
