#ifndef GAMEOBJECT_CAT_H_
#define GAMEOBJECT_CAT_H_

#include "GameObject/moving_object.h"
#include "Model/constants.h"

class Cat : public MovingObject {
 public:
  Cat(const Size& size, double speed, const Point& position);
  ~Cat() override = default;

  void Draw(QPainter* painter) const override;
  void Tick(int time) override;
  void Move(int time) override;

  void SetVelocityFromPlayer(Size velocity);
};

#endif  // GAMEOBJECT_CAT_H_
