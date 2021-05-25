#include "background.h"

#include <QDebug>

void Background::Draw(QPainter* painter, Resizer* resizer, const Point& center) {
  painter->save();
  painter->translate(QPoint(0, 0));
  auto new_coordinates = resizer->GameToWindowCoordinate(center_);
  auto new_coordinates_q = QPoint(new_coordinates.GetX(), new_coordinates.GetY());
  auto
      new_size = resizer->GameToWindowSize(Size(rect_.width(), rect_.height()));
  auto new_rect = QRect(0, 0, new_size.GetWidth(), new_size.GetLength());
  painter->drawPixmap(new_coordinates_q,
                      background_image_);
  painter->restore();
}
