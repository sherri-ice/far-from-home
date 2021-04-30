//
// Created by sienna on 27.04.21.
//

#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QRect>
#include <Model/point.h>
#include <QPainter>
#include "resizer.h"
class ProgressBar : public QRect {
 public:
  ProgressBar() = default;
  explicit ProgressBar(const Point& center);
  ~ProgressBar() = default;

  void SetRange(int min_value, int max_value);
  void Draw(QPainter* painter, Resizer* resizer) const;

  void IncCurrentValue();
  bool IsFull();


 private:
  int cur_value_ = 0;
  int min_value_ = 0;
  int max_value_ = 0;

  Point center_;
};

#endif //PROGRESS_BAR_H
