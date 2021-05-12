#ifndef GAMEOBJECT_RIGID_BODY_H_
#define GAMEOBJECT_RIGID_BODY_H_

#include <QPainter>
#include <View/resizer.h>

#include "Model/point.h"
#include "Model/size.h"

namespace constants {
  const int kCheckIfBordersAreClose = 1;
  const double kCheckIfVelocityIsCloseToZero = 0.05;
}

enum class Border {
  kTop,
  kBottom,
  kLeft,
  kRight,
  kNone
};

class RigidBody {
 public:
  RigidBody() = default;
  RigidBody(const Size* size, const Point* position);
  ~RigidBody() = default;

  QRect GetRect() const;
  bool IsCollide(const RigidBody& other_rigid_body) const;
  void Draw(QPainter* painter, Resizer* resizer) const;

  void SetScaleCoefficients(double coefficient_x, double coefficient_y);

  Point GetCenterOfRigidBody() const;

  bool IfCollisionWillHappen(const RigidBody& other_rigid_body, const Size&
  velocity) const;
  Size GetVelocityToAvoidCollision(const RigidBody& other_rigid_body,
                                   const Size& current_velocity);
  Border GetBorderIfObjectIsNotClose(const QRect& other_rect) const;
  Border GetBorderIfObjectIsClose(const QRect& other_rect) const;

 private:
  const Size* object_size_;
  const Point* object_position_;
  double scale_coefficient_x_{0.8};
  double scale_coefficient_y_{0.3};

  bool need_to_get_around_{false};
  Size saved_vector_to_get_around_{Size(0, 0)};
  Border border_which_is_collide_{Border::kNone};
};

#endif  // GAMEOBJECT_RIGID_BODY_H_
