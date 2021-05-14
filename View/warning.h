#ifndef VIEW_WARNING_H_
#define VIEW_WARNING_H_

#include <QRect>
#include <QPainter>

#include "../GameObject/game_object.h"
#include "../Model/timer.h"
#include "../View/resizer.h"

namespace warning_constants {
const double kAlignCenter = 0.213;
}  // namespace warning_constants

class Warning : public GameObject {
 public:
  Warning() = default;
  Warning(QString message, const Point& center, double font_size, bool
  is_main_warning = false, bool supposed_to_fade = false, int
  time_before_fade = 0);
  ~Warning() override = default;
  void Tick(int delta_time) override;
  void Draw(QPainter* painter, Resizer* resizer) const override;

  void SetShift(int shift);
  void SetIfIsDrawn(bool is_drawn);
  double GetFontSize() const;
  void UpdateMessage(const QString& message);

 private:
  QString message_;
  double font_size_;
  bool is_main_warning_;
  bool supposed_to_fade_;
  int time_before_fade_;
  int shift_{0};
  Timer timer_;
  bool is_drawn_{true};
  int fade_speed_ = 3;
  QColor text_color_ = QColor(0, 50, 0);
  QColor background_color_ = QColor(128, 128, 128, 128);
};

#endif  // VIEW_WARNING_H_
