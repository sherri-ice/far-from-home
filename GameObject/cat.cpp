#include "cat.h"

Cat::Cat(const Size& size, double speed, const Point& position) :
    MovingObject(size, speed, position) {
}

void Cat::Draw(QPainter* painter, Resizer* resizer) const {
  rigid_body_.Draw(painter, resizer);
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
  painter->save();
  painter->setBrush(Qt::red);
  painter->drawEllipse(position.GetX() - size.GetWidth()/2,
                       position.GetY() - size.GetHeight()/2,
                       size.GetWidth(),
                       size.GetHeight());
  painter->restore();
}

void Cat::Tick(int time) {
}

void Cat::Move(int time) {
  if (velocity_.GetLength() > constants::kEpsilon) {
    velocity_ /= velocity_.GetLength();
    position_ += velocity_ * speed_ * time * constants::kTimeScale;
  }
}

void Cat::SetVelocityFromPlayer(Size velocity) {
  velocity_ = velocity;
}

