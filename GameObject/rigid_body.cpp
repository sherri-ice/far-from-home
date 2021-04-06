#include "rigid_body.h"

QRect RigidBody::GetRect() const {
  double x = object_position_->GetX() - scale_coefficient_x_ *
      object_size_->GetWidth() / 2;
  double y = object_position_->GetY() + object_size_->GetHeight() / 2 -
      scale_coefficient_y_ * object_size_->GetHeight();
  return QRect(static_cast<int>(x), static_cast<int>(y),static_cast<int>
  (object_size_->GetWidth() * scale_coefficient_x_),
  static_cast<int>(object_size_->GetWidth() * scale_coefficient_y_));
}

bool RigidBody::IsCollide(const RigidBody& other_rigid_body) const {
  return GetRect().intersects(other_rigid_body.GetRect());
}

void RigidBody::Draw(QPainter* painter) const {
  painter->drawRect(GetRect());
}

RigidBody::RigidBody(const Size* size, const Point* position) : object_size_
  (size), object_position_(position) {
}

void RigidBody::SetScaleCoefficients(double coefficient_x,
                                     double coefficient_y) {
  scale_coefficient_x_ = coefficient_x;
  scale_coefficient_y_ = coefficient_y;
}
