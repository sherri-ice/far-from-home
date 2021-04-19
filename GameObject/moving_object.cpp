#include "moving_object.h"

MovingObject::MovingObject(
    const Size& size, double speed, const Point& position)
    : GameObject(size, position), speed_(speed) {
}

void MovingObject::SetSpeed(double speed) {
  speed_ = speed;
}

void MovingObject::MoveToDestination(int delta_time) {
  if (velocity_.GetLength() > constants::kEpsilon) {
     velocity_ /= velocity_.GetLength();
     velocity_ *= delta_time * speed_ / constants::kTimeScale;
  }
  auto first_vector = (position_ + velocity_).GetVectorTo(destination_);
  auto second_vector = position_.GetVectorTo(destination_);
  if (first_vector.GetWidth() * second_vector.GetWidth() <=
  constants::kEpsilon && first_vector.GetHeight() * second_vector.GetHeight()
  <= constants::kEpsilon) {
    position_ = destination_;
  } else {
    position_ += velocity_;
  }
}
