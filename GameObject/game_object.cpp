#include "game_object.h"

GameObject::GameObject(const Size& size, const Point& position)
    : size_(size), position_(position) {
  rigid_body_ = RigidBody(&size_, &position_);
}

void GameObject::SetSize(Size new_size) {
  size_ = new_size;
}

void GameObject::SetPosition(const Point& position) {
  position_ = position;
}

Size GameObject::GetSize() const {
  return size_;
}

const Point& GameObject::GetPosition() const {
  return position_;
}

RigidBody GameObject::GetRigidBody() const {
  return rigid_body_;
}

void GameObject::SetScaleCoefficientsInRigidBody(double coefficient_x, double
  coefficient_y) {
  rigid_body_.SetScaleCoefficients(coefficient_x, coefficient_y);
}

void GameObject::SetIsDead() {
  is_dead_ = true;
}

bool GameObject::IsDead() const {
  return is_dead_;
}
