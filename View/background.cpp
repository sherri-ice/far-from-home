#include "background.h"

#include <QDebug>

void Background::Draw(QPainter* painter,
                      Resizer* resizer,
                      const Point& center) {
  painter->save();
  painter->translate(-QPoint(center.GetX() - background_image_.width() / 2,
                             center.GetY() - background_image_.height() / 2));

  auto new_coordinates = resizer->GameToWindowCoordinate(center);
  auto new_coordinates_q =
      QPoint(new_coordinates.GetX() - background_image_.width() / 2,
             new_coordinates.GetY() - background_image_.height() / 2);
  auto
      new_size = resizer->GameToWindowSize(Size(background_image_.width(), background_image_.height()));
  painter->drawPixmap(new_coordinates_q.x(),
                      new_coordinates_q.y(),
                      new_size.GetWidth(),
                      new_size.GetHeight(),
                      background_image_);
  painter->restore();
}
