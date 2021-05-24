#include <QPainter>
#include "view_circle.h"

#include <QDebug>

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
    : center_(center), wanted_radius_(radius) {
}

void ViewCircle::Draw(QPainter* painter, Resizer* resizer) const {
  painter->save();
  auto new_center = resizer->GameToWindowCoordinate(center_);
  qDebug() << new_center.GetX() << ' ' << new_center.GetY();
  auto new_size = resizer->GameToWindowSize(Size(radius_, radius_));
  painter->drawEllipse(new_center.GetX() - new_size.GetWidth()/2,
                       new_center.GetY() - new_size.GetHeight()/2,
                       new_size.GetWidth(),
                       new_size.GetHeight());
  painter->restore();
}
void ViewCircle::SetWantedRadius(double wanted_radius) {
  wanted_radius_ = wanted_radius;
}

void ViewCircle::Tick() {
  radius_ += (wanted_radius_ - radius_) / constants::kResizerSpeed;
}
double ViewCircle::GetWantedRadius() const {
  return wanted_radius_;
}
