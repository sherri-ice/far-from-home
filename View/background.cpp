#include "background.h"

#include <QDebug>

void Background::Draw(QPainter* painter,
                      Resizer* resizer,
                      const Point& center) {
  painter->save();
  auto
      new_size = resizer->GameToWindowSize(Size(background_image_.width(),
                                                background_image_.height()));
  auto new_coordinates = resizer->GameToWindowCoordinate(center);
  painter->translate(QPoint(
      center.GetX() - constants::kGameWidth / 2,
      center.GetY() - constants::kGameHeight / 2));

  auto new_coordinates_q =
      QPoint(new_coordinates.GetX(),
             new_coordinates.GetY());

  painter->drawPixmap(new_coordinates_q.x() - new_size.GetWidth() / 2,
                      new_coordinates_q.y() - new_size.GetHeight() / 2,
                      new_size.GetWidth(),
                      new_size.GetHeight(),
                      background_image_);
  painter->restore();
}
