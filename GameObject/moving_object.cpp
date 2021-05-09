#include <iostream>
#include "moving_object.h"

MovingObject::MovingObject(
    const Size& size, double speed, const Point& position)
    : GameObject(size, position), speed_(speed) {
}

void MovingObject::IncSpeed(double speed) {
  speed_ *= speed;
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
  speed_ /= speed;
}

double MovingObject::GetSpeed() {
  return speed_;
}

Size MovingObject::GetVelocity() {
  return velocity_;
}

void MovingObject::SetRunAwayDestination(const Point& first_pos,
                                         const Point& second_pos,
                                         const Point& pos, int x) {
  double y = (first_pos.GetX() - second_pos.GetX()) /
      (second_pos.GetY() - first_pos.GetY()) * x
      + pos.GetY() + (-first_pos.GetX() + second_pos.GetX()) /
      (second_pos.GetY() - first_pos.GetY()) * pos.GetX();
  destination_ = Point(x, y);
}
