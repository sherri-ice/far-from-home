#include "moving_object.h"

MovingObject::MovingObject(
    const Size& size, double speed, const Point& position)
    : GameObject(size, position), speed_(speed) {
}

void MovingObject::SetSpeed(double speed) {
  speed_ = speed;
}

double MovingObject::GetSpeed() const {
  return speed_;
}
