#include "game_object.h"
#include <iostream>

void GameObject::SetSize(Size new_size) {
  size_ = new_size;
}

GameObject::GameObject(const Size& size, const Point& position)
    : size_(size), position_(position) {
  SetRect(position, size);
}

void GameObject::SetPosition(const Point& position) {
  position_ = position;
}

Size GameObject::GetSize() const {
  return size_;
}

void GameObject::SetRect(const Point& pos, const Size& size) {
  rect_ = QRectF(pos.GetX() - size.GetWidth() / 2,
                 pos.GetY() - size.GetHeight() / 2,
                 size.GetWidth(), size.GetHeight());
}

QRectF GameObject::GetRect() const {
  return rect_;
}

bool GameObject::IsCollision(const GameObject& object) const {
  return rect_.intersects(object.GetRect());
}

