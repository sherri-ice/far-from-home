#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>

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

  virtual void SetRect(const Point&, const Size&);
  virtual QRectF GetRect() const;
  virtual bool IsCollision(const GameObject& object) const;

 protected:
  Size size_;
  Point position_;
  QRectF rect_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
