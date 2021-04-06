#include "target_moving_object.h"

TargetMovingObject::TargetMovingObject(Size size,
                                       double speed,
                                       const Point& position) : MovingObject
                                       (size, speed, position) {
}

void TargetMovingObject::MoveToDestination(int time) {
  Size move_direction = position_.GetVectorTo(destination_);

  if (move_direction.GetLength() > constants::kEpsilon) {
    move_direction /= move_direction.GetLength();
    move_direction *= time * speed_ * constants::kTimeScale;
  }
  Size first_vector = (position_ + move_direction).GetVectorTo(destination_);
  Size second_vector = position_.GetVectorTo(destination_);
  if (first_vector.GetWidth() * second_vector.GetWidth() <=
    constants::kEpsilon && first_vector.GetHeight() * second_vector.GetHeight()
    <= constants::kEpsilon) {
    position_ = destination_;
  } else {
    position_ += move_direction;
  }
}

void TargetMovingObject::SetDestination(const Point& destination) {
  destination_ = destination;
}
