#include <iostream>
#include "moving_object.h"

MovingObject::MovingObject(
    const Size& size, double speed, const Point& position)
    : GameObject(size, position), speed_(speed) {
}

void MovingObject::IncSpeed(double speed) {
  std::cout << "                 start speed " << speed_ << std::endl;
  speed_ *= speed;
  std::cout << "                 end speed " << speed_ << std::endl;
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

void MovingObject::DecSpeed(double speed) {
  std::cout << "              dec   start speed " << speed_ << std::endl;
  speed_ /= speed;
  std::cout << "              dec   end speed " << speed_ << std::endl;
}

double MovingObject::GetSpeed() {
  return speed_;
}

Size MovingObject::GetVelocity() {
  return velocity_;
}
