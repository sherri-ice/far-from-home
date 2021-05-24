#include <iostream>
#include "group.h"

Group::Group(double first_radius, double second_radius, Point central_position)
             : first_radius_(first_radius), second_radius_(second_radius),
             central_position_(Point(0, 0)) {}

void Group::Draw(QPainter* painter, Resizer* resizer) const {
  painter->save();
  auto central_position = resizer->GameToWindowCoordinate(central_position_);
  painter->setPen(Qt::blue);
  painter->translate(central_position.GetX(), central_position.GetY());
  Size first_radius = resizer->GameToWindowSize(Size(first_radius_,
                                                     first_radius_));
  painter->drawEllipse(static_cast<int>(-first_radius.GetWidth()),
                       static_cast<int>(-first_radius.GetHeight() *
                           constants::kSemiMinorCoefficient),
                       2 * static_cast<int>(first_radius.GetWidth()),
                       2 * static_cast<int>(first_radius.GetHeight() *
                           constants::kSemiMinorCoefficient));
  Size second_radius = resizer->GameToWindowSize(Size(second_radius_,
                                                     second_radius_));
  painter->drawEllipse(static_cast<int>(-second_radius.GetWidth()),
                       static_cast<int>(-second_radius.GetHeight() *
                           constants::kSemiMinorCoefficient),
                       2 * static_cast<int>(second_radius.GetWidth()),
                       2 * static_cast<int>(second_radius.GetHeight() *
                           constants::kSemiMinorCoefficient));
  painter->restore();
}

void Group::IncGroup() {
  first_radius_ *= constants::kCatGroupIncCoefficient;
  second_radius_ *= constants::kCatGroupIncCoefficient;
}

void Group::DecGroup(int num_of_cats) {
  first_radius_ /= pow(constants::kCatGroupIncCoefficient, num_of_cats);
  second_radius_ /= pow(constants::kCatGroupIncCoefficient, num_of_cats);
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
