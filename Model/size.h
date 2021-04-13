#ifndef MODEL_SIZE_H_
#define MODEL_SIZE_H_

#include <cmath>
#include <utility>

class Size {
 public:
  Size();
  explicit Size(double x, double y) noexcept;

  Size& operator=(const Size& rhs);

  std::pair<double, double> GetSize();
  [[nodiscard]] double GetLength() const;

  Size operator*(double rhs) const;
  Size operator/(double rhs) const;
  const Size& operator*=(double rhs);
  const Size& operator/=(double rhs);

  Size operator+(Size rhs) const;
  Size operator-(Size rhs) const;
  const Size& operator+=(Size rhs);
  const Size& operator-=(Size rhs);

  bool operator==(Size rhs) const;
  bool operator!=(Size rhs) const;

  [[nodiscard]] double GetWidth() const;
  [[nodiscard]] double GetHeight() const;

  void SetWidth(double width);
  void SetHeight(double height);

 private:
  double width_ = 0;
  double height_ = 0;
};

#endif  // MODEL_SIZE_H_

