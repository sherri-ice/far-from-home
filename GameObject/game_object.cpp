#include "game_object.h"

#include <vector>
#include <iostream>

GameObject::GameObject(const Size& size, const Point& position)
    : size_(size), position_(position) {
  rigid_body_ = RigidBody(&size_, &position_);
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
    size_ = to_size;
}

Point GameObject::GetRigidPosition() const {
  return rigid_body_.GetCenterOfRigidBody();
}


void GameObject::Draw(QPainter* painter, Resizer* resizer) const {
        rigid_body_.Draw(painter, resizer);
        painter->save();
        auto position = resizer->GameToWindowCoordinate(position_);
        auto size = resizer->GameToWindowSize(size_);
        painter->translate(position.GetX(), position.GetY());
        int width = static_cast<int>(size.GetWidth());
        int height = static_cast<int>(size.GetHeight());
        painter->drawPixmap(-width / 2, -height / 2, width, height, skin_);
        painter->restore();
}

void GameObject::Tick(int time) {
}

void GameObject::SetSkin(QPixmap skin) {
    skin_ = skin;
}
