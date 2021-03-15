#include "size.h"
#include "constants.h"

Size::Size(double x, double y) noexcept : width_(x), height_(y) {}

Size Size::operator*(double rhs) const {
  return Size(width_ * rhs, height_ * rhs);
}

Size Size::operator/(double rhs) const {
  return Size(width_ / rhs, height_ / rhs);
}

Size &Size::operator*=(double rhs) {
  *this = *this * rhs;
  return *this;
}

Size &Size::operator/=(double rhs) {
  *this = *this / rhs;
  return *this;
}

Size Size::operator+(Size rhs) const {
  return Size(width_ + rhs.width_, height_ + rhs.height_);
}

Size Size::operator-(Size rhs) const {
  return Size(width_ - rhs.width_, height_ - rhs.height_);
}

Size &Size::operator+=(Size rhs) {
  *this = *this + rhs;
  return *this;
}

Size &Size::operator-=(Size rhs) {
  *this = *this - rhs;
  return *this;
}

bool Size::operator==(Size rhs) const {
  return (width_ - rhs.width_ < constants::kEpsilon)
      && (height_ - rhs.height_ < constants::kEpsilon);
}

bool Size::operator!=(Size rhs) const {
  return !(*this == rhs);
}

std::pair<double, double> Size::GetSize() {
  return std::pair(width_, height_);
}

