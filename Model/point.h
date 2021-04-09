#ifndef MODEL_POINT_H_
#define MODEL_POINT_H_

#include "Model/size.h"

class Point {
 public:
  // TODO(anyone): player must appear in the center of the window
  explicit Point(double x = 0., double y = 0.);
  Point& operator=(const Point& point);

  void SetX(double x);
  void SetY(double y);
  [[nodiscard]] double GetX() const;
  [[nodiscard]] double GetY() const;
  Point operator+(const Point& point) const;

  Point operator*(double rhs) const;
  Point operator/(double rhs) const;

  Point operator+(const Size& rhs) const;
  Point operator-(const Size& rhs) const;

  Point& operator+=(const Size& rhs);

  static bool IsClose(const Point& lhs, const Point& rhs);
 private:
  double x_;
  double y_;
};

#endif  // MODEL_POINT_H_
