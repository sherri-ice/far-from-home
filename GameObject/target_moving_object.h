#ifndef GAMEOBJECT_TARGET_MOVING_OBJECT_H_
#define GAMEOBJECT_TARGET_MOVING_OBJECT_H_

#include "GameObject/moving_object.h"
#include "Model/constants.h"

class TargetMovingObject : public MovingObject {
 public:
  TargetMovingObject(Size size, double speed, const Point& position = Point
      (0, 0));
  ~TargetMovingObject() override = default;

  void MoveToDestination(int time);

  void SetDestination(const Point& destination);

 protected:
  Point destination_;
};

#endif  // GAMEOBJECT_TARGET_MOVING_OBJECT_H_
