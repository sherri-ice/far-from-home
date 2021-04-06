#ifndef  GAMEOBJECT_VIEW_CIRCLE_H_
#define  GAMEOBJECT_VIEW_CIRCLE_H_

#include "Model/point.h"
#include "View/resizer.h"

class ViewCircle  {
 public:
  ViewCircle() = default;
  ViewCircle(const Point& center, double radius);

  [[nodiscard]] const Point& GetCenter() const;
  void SetCenter(const Point& center);
  [[nodiscard]] double GetRadius() const;
  void SetRadius(double radius);
  void Draw(QPainter* painter, Resizer* resizer) const;

 private:
  Point center_;
  double radius_ = 20.;
};

#endif  // GAMEOBJECT_VIEW_CIRCLE_H_
