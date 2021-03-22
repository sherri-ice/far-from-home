#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 public:
  MovingObject(Size size,
               double speed,
               const Point& position = Point(0, 0));
  ~MovingObject() override = default;
  virtual void Move(int time) = 0;
  [[nodiscard]] const Point& GetPosition() const;

  virtual void SetVelocity(Size velocity);
  virtual void SetSpeed(double speed);

 protected:
  Size size_;
  double speed_;
  Point position_;
  Size velocity_;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_
