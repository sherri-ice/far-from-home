#ifndef GAMEOBJECT_RIGID_BODY_H_
#define GAMEOBJECT_RIGID_BODY_H_

#include <QPainter>

#include "Model/point.h"
#include "Model/size.h"

class RigidBody {
 public:
  RigidBody() = default;
  RigidBody(const Size* size, const Point* position);
  ~RigidBody() = default;

  QRect GetRect() const;
  bool IsCollide(const RigidBody& other_rigid_body) const;
  void Draw(QPainter* painter) const;

  void SetScaleCoefficients(double coefficient_x, double coefficient_y);

 private:
  const Size* object_size_;
  const Point* object_position_;
  double scale_coefficient_x_{0.8};
  double scale_coefficient_y_{0.3};
};

#endif  // GAMEOBJECT_RIGID_BODY_H_
