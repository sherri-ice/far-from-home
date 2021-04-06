#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>

#include "GameObject/rigid_body.h"
#include "Model/point.h"
#include "Model/size.h"

class GameObject {
 public:
  explicit GameObject(const Size& size, const Point& position = Point(0, 0));
  virtual ~GameObject() = default;

  virtual void SetPosition(const Point& position);
  virtual void Draw(QPainter* painter) const = 0;
  virtual void Tick(int time) = 0;

  virtual Size GetSize() const;
  virtual void SetSize(Size size);
  const Point& GetPosition() const;
  RigidBody GetRigidBody() const;

  void SetScaleCoefficientsInRigidBody(double coefficient_x, double
  coefficient_y);

  void SetIsDead();
  bool IsDead() const;

 protected:
  Size size_;
  Point position_;
  RigidBody rigid_body_;
  bool is_dead_{false};
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
