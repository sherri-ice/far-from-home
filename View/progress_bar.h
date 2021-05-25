#ifndef VIEW_PROGRESS_BAR_H_
#define VIEW_PROGRESS_BAR_H_

#include <QRect>
#include "../Model/point.h"
#include <QPainter>
#include "../Model/timer.h"
#include "resizer.h"

namespace constants {
const int kOffset = 20;
const int kWidth = 150;
const int kHeight = 10;
}  // namespace constants

class ProgressBar : public QRect {
 public:
  ProgressBar() = default;
  ProgressBar(const Point& center, const Size& size);
  ~ProgressBar() = default;

  void SetRange(int min_value, int max_value);
  void Draw(QPainter* painter, Resizer* resizer) const;

  void IncCurrentValue(int delta_time);
  bool IsFull();

  void SetVisible();
  void SetInvisible();
  void SetTimeToBeFull(int time_to_be_full);

 private:
  int cur_value_ = 0;
  int min_value_ = 0;
  int max_value_ = 0;
  int time_to_be_full_ = 0;

  bool is_visible_ = false;
  Point center_;
};

#endif  // VIEW_PROGRESS_BAR_H_
