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

bool Point::IsInEllipse(Point center, double ellipse_radius) const {
  double foci_coefficient = std::sqrt(
      1 - constants::kSemiMinorCoefficient * constants::kSemiMinorCoefficient);
  Point first_foci(center.GetX() + foci_coefficient * ellipse_radius,
                        center.GetY());
  Point second_foci(center.GetX() - foci_coefficient * ellipse_radius,
                    center.GetY());
  return GetVectorTo(first_foci).GetLength() +
      GetVectorTo(second_foci).GetLength()
      <= 2 * ellipse_radius + constants::kEpsilon;
}

Size Point::GetVelocityVector(const Point& destination,
                              double coefficient) const {
  Size velocity = this->GetVectorTo(destination);
  if (velocity.GetLength() > constants::kEpsilon) {
    velocity /= velocity.GetLength();
    velocity *= coefficient;
  }
  Size first_vector = (*this + velocity).GetVectorTo(destination);
  Size second_vector = this->GetVectorTo(destination);
  if (first_vector.GetWidth() * second_vector.GetWidth() <=
      constants::kEpsilon && first_vector.GetHeight() *
      second_vector.GetHeight() <= constants::kEpsilon) {
    velocity = this->GetVectorTo(destination);
  }
  return velocity;
}
