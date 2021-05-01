#include "size.h"
#include "constants.h"

Size::Size() : width_(0.), height_(0.) {
}

Size::Size(double x, double y) noexcept : width_(x), height_(y) {}

Size Size::operator*(double rhs) const {
  return Size(width_ * rhs, height_ * rhs);
}

Size Size::operator/(double rhs) const {
  return Size(width_ / rhs, height_ / rhs);
}

const Size &Size::operator*=(double rhs) {
  *this = *this * rhs;
  return *this;
}

const Size &Size::operator/=(double rhs) {
  *this = *this / rhs;
  return *this;
}

Size Size::operator+(Size rhs) const {
  return Size(width_ + rhs.width_, height_ + rhs.height_);
}

Size Size::operator-(Size rhs) const {
  return Size(width_ - rhs.width_, height_ - rhs.height_);
}

const Size &Size::operator+=(Size rhs) {
  *this = *this + rhs;
  return *this;
}

const Size &Size::operator-=(Size rhs) {
  *this = *this - rhs;
  return *this;
}

bool Size::operator==(Size rhs) const {
  return (std::abs(width_ - rhs.width_) < constants::kEpsilon)
      && (std::abs(height_ - rhs.height_) < constants::kEpsilon);
}

bool Size::operator!=(Size rhs) const {
  return !(*this == rhs);
}

std::pair<double, double> Size::GetSize() {
  return std::pair(width_, height_);
}

double Size::GetLength() const {
  return std::hypot(width_, height_);
}

double Size::GetWidth() const {
  return width_;
}

double Size::GetHeight() const {
  return height_;
}

Size& Size::operator=(const Size& rhs) {
  width_ = rhs.width_;
  height_ = rhs.height_;
  return *this;
}

void Size::SetWidth(double width) {
  width_ = width;
}

void Size::SetHeight(double height) {
  height_ = height;
}
