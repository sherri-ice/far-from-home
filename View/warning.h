#ifndef WARNING_H
#define WARNING_H
#include <QRect>
#include <QPainter>
#include "resizer.h"

namespace warning_constants {
const int offset = 40;
}  // namespace constants

class Warning {
 public:
  explicit Warning(const Point& center);
  ~Warning() = default;

  void Draw(QPainter* painter, Resizer* resizer) const;
  void SetVisible();
  void SetInvisible();

 private:
  QRect rect_ = QRect(0, 0, 10, 10);
  bool is_visible_ = false;
};

#endif //WARNING_H
