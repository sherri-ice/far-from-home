#include "game_object.h"

GameObject::GameObject(const Size& size, const Point& position)
    : size_(size), position_(position) {
  rigid_body_ = RigidBody(&size_, &position_);
}

void GameObject::Draw(QPainter* painter, Resizer* resizer) const {
  rigid_body_.Draw(painter, resizer);
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
  painter->setBrush(Qt::green);
  painter->drawEllipse(position.GetX() - size.GetWidth()/2,
                       position.GetY() - size.GetHeight()/2,
                       size.GetWidth(),
                       size.GetHeight());
  painter->restore();
}

void GameObject::Tick(int time) {
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

const Point& GameObject::GetDrawPosition() const {
  return position_;
}

RigidBody* GameObject::GetRigidBody() {
  return &rigid_body_;
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

void GameObject::Resize(const Size& to_size) {
  // TODO(sherri.ice)
  // Should be changed after declaring animations
}

Point GameObject::GetRigidPosition() const {
  return rigid_body_.GetCenterOfRigidBody();
}
