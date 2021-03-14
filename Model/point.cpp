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

Point Point::operator+(const Point& point) {
  SetX(x_ + point.GetX());
  SetY(y_ + point.GetY());
  return *this;
}

bool Point::IsClose(const Point& lhs, const Point& rhs) {
  return (std::abs(lhs.GetX() - rhs.GetX()) < constants::kEpsilon &&
      std::abs(lhs.GetY() - rhs.GetY()) < constants::kEpsilon);
}

