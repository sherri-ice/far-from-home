#ifndef VIEW_BUTTON_H_
#define VIEW_BUTTON_H_

#include <QFontDatabase>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>

#include <chrono>
#include <memory>
#include <random>
#include <string>

#include "resizer.h"
#include "../Model/constants.h"

class Button : public QPushButton {
 public:
  Button(const Size& button_size, QMainWindow* main_window,
         const QString& default_icon, const QString& active_icon);

  ~Button() override = default;

  void UpdateIcon();
  void SetIsEnter(bool enter);
  void SetGeometry(Point game_coordinate, Resizer resizer);
  Point GetPosition() const;

 private:
  void enterEvent(QEvent*) override;
  void leaveEvent(QEvent*) override;

 private:
  Size button_size_{0, 0};
  Point position_{0, 0};
  QIcon default_icon_;
  QIcon active_icon_;
  bool have_entered_event_ = false;

  static std::mt19937 random_generator_;
};

#endif  // VIEW_BUTTON_H_

