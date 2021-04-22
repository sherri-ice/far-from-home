#include "rigid_body.h"
#include <iostream>
QRect RigidBody::GetRect() const {
  double x = object_position_->GetX() - scale_coefficient_x_ *
      object_size_->GetWidth() / 2;
  double y = object_position_->GetY() + object_size_->GetHeight() / 2 -
      scale_coefficient_y_ * object_size_->GetHeight();
  return QRect(static_cast<int>(x), static_cast<int>(y), static_cast<int>
  (object_size_->GetWidth() * scale_coefficient_x_), static_cast<int>
  (object_size_->GetHeight() * scale_coefficient_y_));
}

bool RigidBody::IsCollide(const RigidBody& other_rigid_body) const {
  return GetRect().intersects(other_rigid_body.GetRect());
}

void RigidBody::Draw(QPainter* painter, Resizer* resizer) const {
  auto rect = GetRect();
  std::cout << "-------------------" << std::endl;
  std::cout << "Rect width " << " " << rect.width() << " rect height " << rect.height() << std::endl;
    std::cout << "-------------------" << std::endl;
  auto game_size = Size(rect.width(), rect.height());
  auto window_size = resizer->GameToWindowSize(game_size);
  auto game_coordinate = Point(rect.x(), rect.y());
  auto window_coordinates = resizer->GameToWindowCoordinate(game_coordinate);
  rect.setX(window_coordinates.GetX());
  rect.setY(window_coordinates.GetY());
  rect.setWidth(window_size.GetWidth());
  rect.setHeight(window_size.GetHeight());
  painter->drawRect(rect);
}

RigidBody::RigidBody(const Size* size, const Point* position) : object_size_
  (size), object_position_(position) {
}

void RigidBody::SetScaleCoefficients(double coefficient_x,
                                     double coefficient_y) {
  scale_coefficient_x_ = coefficient_x;
  scale_coefficient_y_ = coefficient_y;
}

Point RigidBody::GetCenterOfRigidBody() const {
  double y = object_position_->GetY() + object_size_->GetHeight() / 2 -
      object_size_->GetHeight() * scale_coefficient_y_ / 2;
  return Point(object_position_->GetX(), y);
}
