#ifndef GAMEOBJECT_CAT_H_
#define GAMEOBJECT_CAT_H_

#include "GameObject/moving_object.h"

class Cat : public MovingObject {
 public:
  Cat() = default;
  ~Cat() override = default;

  void Draw(QPainter* painter) override;
  void Tick(int time) override;
  void Move(int direction) override;

 private:
};

#endif  // GAMEOBJECT_CAT_H_
