#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 public:
  MovingObject(const Size& size,
               double speed,
               const Point& position = Point(0, 0));
  ~MovingObject() override = default;
  virtual void Move(int time) = 0;

  virtual void SetSpeed(double speed);
  bool IsMoving();



protected:
    double speed_;
    Size velocity_;
    bool is_moving_ = false;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_
