#include "cat.h"

Cat::Cat(const Size& size, double speed, const Point& position) :
    MovingObject(size, speed, position) {
}

void Cat::Draw(QPainter* painter, Resizer* resizer) {
  rigid_body_.Draw(painter, resizer);
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
    painter->drawPixmap(position.GetX() - size.GetWidth() / 2,
                      position.GetY() - size.GetHeight() / 2,
                      size.GetWidth(),
                      size.GetHeight(),
                      object_animation_.GetCurrentFrame());
  painter->restore();
}

void Cat::Tick(int delta_time) {
  if (velocity_.GetLength() > constants::kEpsilon) {
    is_moving_ = true;
    velocity_ /= velocity_.GetLength();
    velocity_ *= speed_ * delta_time / constants::kTimeScale;
  } else {
    is_moving_ = false;
  }
    object_animation_.Tick(delta_time, GetAnimation());
    was_moving_ = is_moving_;
}

void Cat::SetVelocityFromPlayer(Size velocity) {
  velocity_ = velocity;
}
