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
    : center_(center), wanted_radius_(radius) {
}

void ViewCircle::Draw(QPainter* painter, Resizer* resizer) const {
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
