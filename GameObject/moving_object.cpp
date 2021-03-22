#include "moving_object.h"

const Point& MovingObject::GetPosition() const {
  return position_;
}

MovingObject::MovingObject(
    Size size, double speed, const Point& position)
    : GameObject(size, position), speed_(speed) {
}

void MovingObject::SetSpeed(double speed) {
  speed_ = speed;
}

void MovingObject::SetVelocity(Size velocity) {
  velocity_ = velocity;
}
