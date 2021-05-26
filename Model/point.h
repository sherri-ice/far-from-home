#ifndef MODEL_POINT_H_
#define MODEL_POINT_H_

#include "../Model/size.h"
#include "constants.h"

class Point {
 public:
  explicit Point(double x = constants::kGameWidth / 2,
                 double y = constants::kGameHeight / 2);
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
  bool operator==(const Point& rhs) const;
  bool operator!=(const Point& rhs) const;

  static bool IsClose(const Point& lhs, const Point& rhs);
  Size GetVelocityVector(const Point& destination, double
  coefficient) const;

  Size GetVectorTo(const Point& destination) const;
  bool IsInEllipse(Point position, double ellipse_radius) const;

 private:
  double x_;
  double y_;
};

#endif  // MODEL_POINT_H_
