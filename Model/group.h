#ifndef MODEL_GROUP_H_
#define MODEL_GROUP_H_

#include <QPainter>
#include "point.h"
#include "View/resizer.h"

class Group {
 public:
  friend class Player;
  Group(double  first_radius, double second_radius,
        Point central_position = Point(0, 0));
  ~Group() = default;

  void Draw(QPainter* painter, Resizer* resizer) const;
  void Tick(int delta_time);
  void Move(int delta_time);
  void IncGroup();
  void DecGroup(int num_of_cats = 1);
  void SetSpeed(double speed);

  double first_radius_;
  double second_radius_;

  double speed_;
  Point central_position_;
  Size velocity_;
};

#endif  //  MODEL_GROUP_H_
