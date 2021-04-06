#include "cat.h"

Cat::Cat(const Size& size, double speed, const Point& position) :
    MovingObject(size, speed, position) {
}

void Cat::Draw(QPainter* painter) const {
  rigid_body_.Draw(painter);
  painter->save();
  painter->translate(position_.GetX(), position_.GetY());
  int object_width = static_cast<int>(GetSize().GetWidth());
  int object_height = static_cast<int>(GetSize().GetHeight());
  painter->setBrush(Qt::red);
  painter->drawEllipse(-object_width / 2,
                       -object_height / 2,
                       object_width,
                       object_height);
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
