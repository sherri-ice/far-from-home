#include <Controller/abstract_controller.h>
#include "cat.h"

void Cat::Draw(QPainter* painter) {
  painter->save();
  auto position = GetPosition();
  painter->translate(position.GetX(), position.GetY());
  painter->setBrush(Qt::red);
  painter->drawEllipse(0, 0, 100, 100);
  painter->restore();
}

void Cat::Tick(int time) {
}

void Cat::Move(int direction) {
  if (direction == static_cast<int>(Directions::kLeft)) {
    SetPosition(position_ + Point(-10, 0));
  }
  if (direction == static_cast<int>(Directions::kUp)) {
    SetPosition(position_ + Point(0, -10));
  }
  if (direction == static_cast<int>(Directions::kDown)) {
    SetPosition(position_ + Point(0, 10));
  }
  if (direction == static_cast<int>(Directions::kRight)) {
    SetPosition(position_ + Point(10, 0));
  }
}
