#include <cmath>

#include "point.h"
#include "constants.h"

Point::Point(double x, double y) : x_(x), y_(y) {
}

Point& Point::operator=(const Point& point) {
  this->SetX(point.GetX());
  this->SetY(point.GetY());
  return *this;
}

void Point::SetY(double y) {
  y_ = y;
}

void Point::SetX(double x) {
  x_ = x;
}

double Point::GetX() const {
  return x_;
}

double Point::GetY() const {
  return y_;
}

Point Point::operator+(const Point& point) const {
  return Point(x_ + point.GetX(), y_ + point.GetY());
}

bool Point::IsClose(const Point& lhs, const Point& rhs) {
  return (std::abs(lhs.GetX() - rhs.GetX()) < constants::kEpsilon &&
      std::abs(lhs.GetY() - rhs.GetY()) < constants::kEpsilon);
}

Point Point::operator+(const Size& rhs) const {
  return Point(x_ + rhs.GetWidth(), y_ + rhs.GetHeight());
}

Point& Point::operator+=(const Size& rhs) {
  *this = *this + rhs;
  return *this;
}


Size Point::GetVectorTo(const Point& destination) const {
  return Size(destination.x_ - x_, destination.GetY() - y_);
}

bool Point::operator==(const Point& rhs) const {
  return (x_ == rhs.x_) && (y_ == rhs.y_);
}

bool Point::operator!=(const Point& rhs) const {
  return !(*this == rhs);
}

Point Point::operator-(const Size& rhs) const {
  return Point(x_ - rhs.GetWidth(), y_ - rhs.GetHeight());
}

Point Point::operator*(double rhs) const {
  return Point(x_ * rhs, y_ * rhs);
}

Point Point::operator/(double rhs) const {
  return Point(x_ / rhs, y_ / rhs);
}

