#include "game_object.h"

void GameObject::SetSize(Size new_size) {
  size_ = new_size;
}

GameObject::GameObject(const Size& size, const Point& position)
    : size_(size), position_(position) {
}

void GameObject::SetPosition(const Point& position) {
  position_ = position;
}

Size GameObject::GetSize() const {
  return size_;
}

void GameObject::Resize(const Size& to_size) {
  // TODO(sherri.ice)
  // Should be changed after declaring animations
}




