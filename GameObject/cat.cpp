#include "cat.h"

Cat::Cat(Size size, double speed, const Point& position) :
    MovingObject(size, speed, position) {
}

void Cat::Draw(QPainter* painter) {
  painter->save();
  auto position = GetPosition();
  painter->translate(position.GetX(), position.GetY());
  painter->setBrush(Qt::red);
  painter->drawEllipse(0, 0, static_cast<int>(GetSize().GetWidth()),
                       static_cast<int>(GetSize().GetHeight()));
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
