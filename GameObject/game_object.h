#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>
#include <vector>
#include <QFontDatabase>
#include "../GameObject/rigid_body.h"
#include "../Model/point.h"
#include "../Model/size.h"
#include "../View/resizer.h"

class GameObject {
 public:
  GameObject() = default;
  explicit GameObject(const Size& size, const Point& position = Point(0, 0));
  virtual ~GameObject() = default;

  virtual void SetPosition(const Point& position);
  virtual void Draw(QPainter* painter, Resizer* resizer) const;
  virtual void Tick(int time);
  void SetSkin(QPixmap skin);

  virtual void Resize(const Size& to_size);

  [[nodiscard]] virtual Size GetSize() const;
  virtual void SetSize(Size size);
  const Point& GetDrawPosition() const;
  Point GetRigidPosition() const;
  RigidBody* GetRigidBody();

  void SetScaleCoefficientsInRigidBody(double coefficient_x, double
  coefficient_y);


  void SetIsDead();
  bool IsDead() const;

  int GetSkinId() const;
  void SetSkinId(int skin_id);

 protected:
  QPixmap skin_;
  int skin_id_ = 0;
  Size size_ = Size(40, 40);
  Point position_;
  RigidBody rigid_body_;
  bool is_dead_{false};
  bool is_visible_ = true;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
