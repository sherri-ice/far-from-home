#include "background.h"

void Background::Draw(QPainter* painter,
                      Resizer* resizer,
                      const Point& center) {
  painter->save();
  painter->setBrush(QBrush(QColor(124, 252, 0)));
  painter->drawRect(QRect(0, 0, 7000, 7000));
  painter->restore();
}
