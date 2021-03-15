#ifndef MODEL_SIZE_H_
#define MODEL_SIZE_H_

#include <utility>
#include <cmath>

class Size {
 public:
  Size() = default;
  Size(double x, double y) noexcept;

  std::pair<double, double> GetSize();

  Size operator*(double rhs) const;
  Size operator/(double rhs) const;
  Size& operator*=(double rhs);
  Size& operator/=(double rhs);

  Size operator+(Size rhs) const;
  Size operator-(Size rhs) const;
  Size& operator+=(Size rhs);
  Size& operator-=(Size rhs);

  bool operator==(Size rhs) const;
  bool operator!=(Size rhs) const;

 private:
  double width_ = 0;
  double height_ = 0;
};


#endif  // MODEL_SIZE_H_
