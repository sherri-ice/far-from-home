#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QRect>
#include <QPixmap>
#include "../Model/constants.h"
#include "resizer.h"
#include <QPainter>

class Background {
 public:
  Background() = default;
  ~Background() = default;

  void Draw(QPainter* painter, Resizer* resizer, const Point& center);

 private:
  QRect rect_ = QRect(0, 0, constants::kGameWidth, constants::kGameHeight);
  QPixmap background_image_ = QPixmap(":images/texture/background.png");
  Point center_ = Point();

};

#endif //BACKGROUND_H
