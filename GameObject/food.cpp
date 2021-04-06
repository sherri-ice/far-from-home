#include <experimental/random>

#include "food.h"

Food::Food(const Size& size, const Point& position) : GameObject(size,
                                                                 position) {
}

void Food::Draw(QPainter* painter) const {
  rigid_body_.Draw(painter);
  painter->save();
  auto position = position_;
  painter->translate(position.GetX(), position.GetY());
  painter->setBrush(Qt::yellow);
  int width = static_cast<int>(GetSize().GetWidth());
  int height = static_cast<int>(GetSize().GetHeight());
  painter->drawEllipse(-width / 2, -height / 2, width, height);
  painter->restore();
}

void Food::Tick(int time) {
}
