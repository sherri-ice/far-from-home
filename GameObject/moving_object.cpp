#include "moving_object.h"

const Point& MovingObject::GetPosition() const {
  return position_;
}

MovingObject::MovingObject(Size size,
                           double speed,
                           const Point& position,
                           const Point& destination) :
                           GameObject(size,
                                            position),
                           destination_(destination),
                           speed_(speed) {
}

void MovingObject::MoveToDestination() {
  // TODO(anyone)
}

void MovingObject::SetSpeed(double speed) {
  speed_ = speed;
}

bool MovingObject::IsDead() const {
  return is_dead_;
}

bool MovingObject::IsMovable() const {
  return is_movable_;
}

