#include "cat.h"

Cat::Cat(const Size& size, double speed, const Point& position) :
    MovingObject(size, speed, position), home_position_(position) {
}

void Cat::Draw(QPainter* painter, Resizer* resizer) const {
  rigid_body_.Draw(painter, resizer);
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
  painter->setBrush(Qt::red);
  painter->drawEllipse(position.GetX() - size.GetWidth()/2,
                       position.GetY() - size.GetHeight()/2,
                       size.GetWidth(),
                       size.GetHeight());
  painter->restore();
}

void Cat::Tick(int time) {
  if (velocity_.GetLength() > constants::kEpsilon) {
    velocity_ /= velocity_.GetLength();
    velocity_ *= speed_ * time * constants::kTimeScale;
  }
  if (!GetIsInGroup()) {
    auto distance = position_.GetVectorTo(home_position_).GetLength();
    if (distance < 0.5) {
      velocity_ = Size(0, 0);
    }
  }
}

bool Cat::GetIsInGroup() const {
  return is_in_group_;
}

void Cat::SetVelocityFromPlayer(Size velocity) {
  velocity_ = velocity;
}

void Cat::SetIsInGroup(bool in_group) {
  is_in_group_ = in_group;
}

Point Cat::GetHomePosition() const {
  return home_position_;
}
