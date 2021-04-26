#include "food.h"

Food::Food(const Size& size, const Point& position) : GameObject(size,
                                                                 position) {
}

void Food::Draw(QPainter* painter, Resizer* resizer) const {
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

void Food::Tick(int time) {
}

void Food::SetSkin(QPixmap skin) {
    skin_ = skin;
}
