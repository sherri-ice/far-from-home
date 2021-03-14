#ifndef MODEL_POINT_H_
#define MODEL_POINT_H_

class Point {
 public:
  explicit Point(double x = 0., double y = 0.);
  Point& operator=(const Point& point);

  void SetX(double x);
  void SetY(double y);
  [[nodiscard]] double GetX() const;
  [[nodiscard]] double GetY() const;
  Point operator+(const Point& point);

  static bool IsClose(const Point& lhs, const Point& rhs);
 private:
  double x_;
  double y_;
};

#endif  // MODEL_POINT_H_
