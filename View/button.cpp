#include <QtWidgets/QStyle>
#include "button.h"

std::mt19937 Button::random_generator_ = std::mt19937(
    std::chrono::system_clock::now().time_since_epoch().count());

Button::Button(const Size& button_size,
               QMainWindow* main_window,
               const QString& default_icon,
               const QString& active_icon)
    : QPushButton(main_window),
      button_size_(button_size),
      default_icon_(default_icon),
      active_icon_(active_icon) {
  setIcon(default_icon_);
  setCursor(Qt::PointingHandCursor);
  setMouseTracking(true);
  setStyleSheet("background: transparent;");
  setFocusPolicy(Qt::NoFocus);
}

void Button::UpdateIcon() {
  setIcon((have_entered_event_) ? active_icon_ : default_icon_);
}

void Button::SetIsEnter(bool enter) {
  have_entered_event_ = enter;
}

void Button::SetGeometry(
    Point game_coordinate, Resizer resizer) {
  position_ = game_coordinate;
  auto window_coordinate = resizer.GameToWindowCoordinate(game_coordinate);
  Size window_size = resizer.GameToWindowSize(button_size_);
  this->setGeometry(window_coordinate.GetX(), window_coordinate.GetY(),
                    window_size.GetWidth(), window_size.GetHeight());
  setIconSize(QSize(window_size.GetWidth(), window_size.GetHeight()));
}

void Button::enterEvent(QEvent*) {
  have_entered_event_ = true;
  setIcon(active_icon_);
}

void Button::leaveEvent(QEvent*) {
  have_entered_event_ = false;
  setIcon(default_icon_);
}

Point Button::GetPosition() const {
  return position_;
}
