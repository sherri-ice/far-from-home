#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>

#include "Model/point.h"
#include "Model/size.h"

class GameObject {
 public:
  explicit GameObject(const Size& size, const Point& position = Point(0, 0));
  GameObject() = default;
  virtual ~GameObject() = default;

  virtual void SetPosition(const Point& position);
  virtual void Draw(QPainter* painter) = 0;
  virtual void Tick(int time) = 0;

  virtual Size GetSize() const;
  virtual void SetSize(Size size);

 protected:
  Size size_;
  Point position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
