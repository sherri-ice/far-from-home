#ifndef VIEW_BACKGROUND_H_
#define VIEW_BACKGROUND_H_

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
};

#endif  // VIEW_BACKGROUND_H_
