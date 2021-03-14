#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "game_object.h"



class MovingObject : public GameObject {
 public:
  MovingObject() = default;
  MovingObject(Size size,
               double speed,
               const Point& position = Point(0, 0),
               const Point& destination = Point(0, 0));
  ~MovingObject() override = default;
  void MoveToDestination();
  void SetSpeed(double speed);
  virtual void Move(int direction) = 0;
  [[nodiscard]] virtual bool IsDead() const;
  [[nodiscard]] virtual bool IsMovable() const;
  [[nodiscard]] const Point& GetPosition() const;
 private:
  Point destination_;
  double speed_;
  bool is_dead_ = false;
  bool is_movable_ = true;
 protected:
  Point position_;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_
