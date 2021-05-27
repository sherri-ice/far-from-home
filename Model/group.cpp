#include "group.h"

Group::Group(double first_radius, double second_radius, Point central_position)
             : first_radius_(first_radius), second_radius_(second_radius),
             central_position_(Point()) {}

void Group::Draw(QPainter* painter, Resizer* resizer) const {
  painter->save();
  auto central_position = resizer->GameToWindowCoordinate(central_position_);
  painter->translate(central_position.GetX(), central_position.GetY());
  painter->restore();
}

void Group::IncGroup() {
  first_radius_ *= constants::kCatGroupIncCoefficient;
  second_radius_ *= constants::kCatGroupIncCoefficient;
}

void Group::Tick(int delta_time) {
  if (velocity_.GetLength() > constants::kEpsilon) {
    velocity_ /= velocity_.GetLength();
    velocity_ *= speed_ * delta_time / constants::kTimeScale;
  }
}

void Group::Move() {
  central_position_ += velocity_;
}

void Group::DecGroup(int num_of_cats) {
  if (num_of_cats) {
    first_radius_ /= num_of_cats * constants::kCatGroupIncCoefficient;
    second_radius_ /= num_of_cats * constants::kCatGroupIncCoefficient;
  }
}

void Group::SetSpeed(double speed) {
  speed_ = speed;
}

void Group::SetCentralPosition(const Point& central_position) {
  central_position_ = central_position;
}


