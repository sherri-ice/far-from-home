#ifndef GAMEOBJECT_RIGID_BODY_H_
#define GAMEOBJECT_RIGID_BODY_H_

#include <QPainter>
#include "../View/resizer.h"

#include "../Model/point.h"
#include "../Model/size.h"

namespace constants {
  const double kIntersectedBorder = 4.5;
}

enum class Border {
  kTop,
  kBottom,
  kLeft,
  kRight,
  kNone
};

struct Rect {
  double x;
  double y;
  double width;
  double height;

  bool operator==(const Rect& rhs) const {
    return std::abs(x - rhs.x) < constants::kEpsilon && std::abs(y - rhs.y) <
        constants::kEpsilon && std::abs(width - rhs.width) < constants::kEpsilon
        && std::abs(height - rhs.height) < constants::kEpsilon;
  }
};

class RigidBody {
 public:
  RigidBody() = default;
  RigidBody(const Size* size, const Point* position);
  ~RigidBody() = default;

  Rect GetRect() const;
  Rect GetRectInNewPosition(const Point& position) const;
  static bool Intersects(const Rect& first_rect, const Rect& second_rect);
  bool IsCollide(const RigidBody& other_rigid_body) const;
  bool IsCollide(const Rect& other_rect) const;
  void Draw(QPainter* painter, Resizer* resizer) const;

  void SetScaleCoefficients(double coefficient_x, double coefficient_y);

  Point GetCenterOfRigidBody() const;

  bool IfCollisionWillHappen(const RigidBody& other_rigid_body, const Size&
  velocity, const Size& other_velocity = Size(0, 0)) const;
  Size GetVelocityToGoAround(const RigidBody& other_rigid_body,
                             const Size& current_velocity, const Size&
                             other_velocity = Size(0, 0));
  Border GetIntersectedBorder(const Rect& other_rect) const;
  Border GetIntersectedBorderIfNone(const Rect& other_rect) const;
  bool IsDestinationCollideWithRect(const Rect& other_rect) const;
  Point GetObjectPosition() const;

  bool IsInside(const QRect& other_rect) const;

 private:
  const Size* object_size_;
  const Point* object_position_;
  double scale_coefficient_x_{0.8};
  double scale_coefficient_y_{0.3};

  bool correct_saved_velocity_{true};
  Size saved_vector_to_get_around_{Size(0, 0)};
  Border border_which_is_collide_{Border::kNone};
};

#endif  // GAMEOBJECT_RIGID_BODY_H_
