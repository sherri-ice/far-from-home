#include "moving_object.h"

MovingObject::MovingObject(
    const Size& size, double speed, const Point& position)
    : GameObject(size, position), speed_(speed) {
}

void MovingObject::SetSpeed(double speed) {
  speed_ = speed;
}

Size MovingObject::GetVelocity() const {
  return velocity_;
}

void MovingObject::SetDestination(const Point& destination) {
  destination_ = destination;
}

void MovingObject::SetVelocity(Size velocity) {
  velocity_ = velocity;
}

void MovingObject::Move(int delta_time) {
  position_ += velocity_;
}
