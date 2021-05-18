#ifndef VIEW_GLOBAL_PROGRESS_BAR_H_
#define VIEW_GLOBAL_PROGRESS_BAR_H_

#include <QPainter>

#include "../Model/constants.h"
#include "../Model/point.h"
#include "../Model/size.h"

class GlobalProgressBar {
 public:
  GlobalProgressBar(int max_value, int current_value, const Point& position =
      Point(25, 25), const Size& size = Size(210, 50));
  ~GlobalProgressBar() = default;

  void UpdateCurrentValue(int new_value);
  void Draw(QPainter* painter) const;

  void SetMaxValue(int max_value);
  void SetSkin(const QPixmap& skin);

 private:
  int max_value_;
  int current_value_;
  Point position_;
  Size size_;
  QPixmap skin_{};

  int inner_width_{154};
  int inner_height_{32};
  int inner_small_height_{6};
  int height_shift_{11};
  int width_shift_{45};

  QColor light_blue_ = QColor(123, 104, 238);
  QColor blue_ = QColor(72, 61, 139);
  QColor light_green = QColor(124, 252, 0);
  QColor green_ = QColor(0, 255, 0);
  QColor light_orange_ = QColor(255, 165, 0);
  QColor orange_ = QColor(255, 140, 0);
  QColor light_red_ = QColor(178, 34, 34);
  QColor red_ = QColor(139, 0, 0);
};

#endif  // VIEW_GLOBAL_PROGRESS_BAR_H_
