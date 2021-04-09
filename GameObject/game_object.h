#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include <QPainter>

#include "Model/point.h"
#include "Model/size.h"
#include "View/resizer.h"

class GameObject {
 public:
  explicit GameObject(const Size& size, const Point& position = Point(0, 0));
  virtual ~GameObject() = default;

  virtual void SetPosition(const Point& position) = 0;
  virtual void Draw(QPainter* painter, Resizer* resizer) const = 0;
  virtual void Tick(int time) = 0;

  virtual void Resize(const Size& to_size);

  [[nodiscard]] virtual Size GetSize() const;
  virtual void SetSize(Size size);

 protected:
  Size size_ = Size(40, 40);
  Point position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
