#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"

class MovingObject : public GameObject {
 public:
  MovingObject(const Size& size,
               double speed,
               const Point& position = Point(0, 0));
  ~MovingObject() override = default;
  virtual void Move(int delta_time);

  virtual void IncSpeed(double speed);
  virtual void DecSpeed(double speed);
  virtual void SetVelocity(Size velocity);
  virtual void SetRunAwayDestination(const Point& first_pos,
                                     const Point& second_pos,
                                     const Point& pos,
                                     int x);
  virtual double GetSpeed();
  virtual Size GetVelocity();
  void SetDestination(const Point& destination);

 protected:
  double speed_;
  Point destination_;
  Size velocity_;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_
