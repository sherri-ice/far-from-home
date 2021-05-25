#ifndef VIEW_PROGRESS_BAR_H_
#define VIEW_PROGRESS_BAR_H_

#include <QPainter>
#include <QRect>

#include "../Model/point.h"
#include "../Model/timer.h"
#include "resizer.h"

namespace progress_bar_constants {
const int kOffset = 50;
const int kWidth = 150;
const int kHeight = 30;
const double kGetInnerWidthCoeff = 0.893;
const double kGetInnerHeightCoeff = 0.64;
const double kGetInnerSmallHeightCoeff = 0.17;
const double kGetWidthShiftCoeff = 0.055;
const double kGetHeightShiftCoeff = 0.22;
}  // namespace progress_bar_constants

class ProgressBar : public QRect {
 public:
  ProgressBar() = default;
  ProgressBar(const Point& center);
  ~ProgressBar() = default;

  void SetRange(int min_value, int max_value);
  void Draw(QPainter* painter, Resizer* resizer) const;

  void IncCurrentValue(int delta_time);

  void SetVisible();
  void SetInvisible();

 private:
  int cur_value_ = 0;
  int min_value_ = 0;
  int max_value_ = 0;
  bool is_visible_ = false;

  QPixmap skin_ = QPixmap("../images/objects/progress_bar/Frame 1.png");
  QColor light_blue_ = QColor(123, 104, 238);
  QColor blue_ = QColor(72, 61, 139);
  QColor pink_ = QColor(218, 112, 214);
  QColor light_pink_ = QColor(238, 130, 238);
};

#endif  // VIEW_PROGRESS_BAR_H_
