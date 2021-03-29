#include "cat.h"

Cat::Cat(Size size, double speed, const Point& position) :
    MovingObject(size, speed, position) {
}

void Cat::Draw(QPainter* painter) const {
  painter->save();
  auto position = GetPosition();
  painter->translate(position.GetX(), position.GetY());
  painter->setBrush(Qt::red);
  int object_width = static_cast<int>(GetSize().GetWidth());
  int object_height = static_cast<int>(GetSize().GetHeight());
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

void Cat::SetPosition(const Point& position) {
  position_ = position;
}

void Cat::SetVelocityFromPlayer(Size velocity) {
  velocity_ = velocity;
}
