#include <QPainter>
#include "view_circle.h"


const Point& ViewCircle::GetCenter() const {
  return center_;
}

void ViewCircle::SetCenter(const Point& center) {
  center_ = center;
}

double ViewCircle::GetRadius() const {
  return radius_;
}

void ViewCircle::SetRadius(double radius) {
  radius_ = radius;
}

ViewCircle::ViewCircle(const Point& center, double radius)
    : center_(center), radius_(radius) {
}

void ViewCircle::Draw(QPainter* painter, Resizer* resizer) const {
  painter->save();
  auto new_center = resizer->GameToWindowCoordinate(center_);
  auto new_size = resizer->GameToWindowSize(Size(radius_, radius_));
  painter->drawEllipse(new_center.GetX() - new_size.GetWidth()/2,
                       new_center.GetY() - new_size.GetHeight()/2,
                       new_size.GetWidth(),
                       new_size.GetHeight());
  painter->restore();
}
