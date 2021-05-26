#include <vector>

#include "game_object.h"

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
  if (is_visible_) {
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
}

void GameObject::SetSkin(QPixmap skin) {
    skin_ = skin;
}

int GameObject::GetSkinId() const {
  return skin_id_;
}

void GameObject::SetSkinId(int skin_id) {
  skin_id_ = skin_id;
}

Size GameObject::GetDrawSize(const Size& object_size) const {
  double object_width = object_size.GetWidth();
  double object_height = object_size.GetHeight();
  if (skin_.width() >= skin_.height()) {
    double scale_coeff = static_cast<double>(skin_.height()) / skin_.width();
    object_height *= scale_coeff;
  } else {
    double scale_coeff = static_cast<double>(skin_.width()) / skin_.height();
    object_width *= scale_coeff;
  }
  return Size(object_width, object_height);
}
