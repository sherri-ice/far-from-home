#ifndef  GAMEOBJECT_VIEW_CIRCLE_H_
#define  GAMEOBJECT_VIEW_CIRCLE_H_

#include "../Model/point.h"
#include "../View/resizer.h"

class ViewCircle {
 public:
  ViewCircle() = default;
  ViewCircle(const Point& center, double radius);

  [[nodiscard]] const Point& GetCenter() const;
  void SetCenter(const Point& center);
  [[nodiscard]] double GetRadius() const;
  void SetRadius(double radius);
  void Draw(QPainter* painter, Resizer* resizer) const;
  void SetWantedRadius(double wanted_radius);
  void Tick();
  [[nodiscard]] double GetWantedRadius() const;

 private:
  Point center_{Point(constants::kGameWidth / 2, constants::kGameHeight / 2)};
  double radius_{constants::kViewCircleMax};
  double wanted_radius_{constants::kViewCircleDefault};
};

#endif  // GAMEOBJECT_VIEW_CIRCLE_H_
