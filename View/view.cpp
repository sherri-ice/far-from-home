#include "view.h"
#include "../Model/constants.h"

#include <QKeyEvent>
#include <QGraphicsScene>
#include <utility>
#include <vector>
#include <algorithm>


View::View(AbstractController* controller,
           std::shared_ptr<Model> model)
    : controller_(controller),
      model_(std::move(model)) {
  setWindowTitle(constants::kApplicationName);
  resize(constants::kGameWidth, constants::kGameHeight);
  resizer_.ChangeSystem(width(), height());

  setMouseTracking(true);
  setFocusPolicy(Qt::ClickFocus);

  // controller->StartGame();
  show();
  time_between_ticks_.start();
  controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
  view_timer_.start();
}

void View::SecondConstructorPart() {
  button_handler_ = std::make_shared<ButtonHandler>(this, controller_);
  Resize();
  button_handler_->SetGameUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  // button_handler_->SetSettingsUiVisible(false);
  button_handler_->SetMainMenuUiVisible(false);
  is_model_loaded_ = true;
}

void View::paintEvent(QPaintEvent*) {
  QPainter painter(this);
  if (!is_model_loaded_) {
    return;
  }
// todo background
  painter.drawPixmap(0, 0, controller_->GetBackground(
      button_handler_->GetWindowType()));
  window_type_ = button_handler_->GetWindowType();
  switch (window_type_) {
    case WindowType::kMainMenu: {
      DrawMainMenu(&painter);
      break;
    }
    case WindowType::kGame: {
      button_handler_->SetMainMenuUiVisible(false);
      button_handler_->SetPauseMenuUiVisible(false);
      button_handler_->SetGameUiVisible(true);
      DrawGameObjects(&painter);
      break;
    }
    // case WindowType::kSettings: {
    //   DrawSettings(&painter);
    //   break;
    // }
    case WindowType::kPauseMenu: {
      DrawPauseMenu(&painter);
      break;
    }
    default: break;
  }
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_) {
    if (!is_model_loaded_) {
      repaint();
      controller_->SecondConstructorPart();
      return;
    }
    int delta_time = time_between_ticks_.elapsed();
    time_between_ticks_.restart();
    controller_->Tick(controller_->GetCurrentTime() + delta_time);
  }
  repaint();
}

void View::keyPressEvent(QKeyEvent* event) {
  pressed_keys_[event->key()] = true;
}

Size View::GetPlayerVelocity() {
  if (pressed_keys_[Qt::Key_Up]) {
    player_velocity_ += Size(0, -1);
  }
  if (pressed_keys_[Qt::Key_Down]) {
    player_velocity_ += Size(0, 1);
  }
  if (pressed_keys_[Qt::Key_Left]) {
    player_velocity_ += Size(-1, 0);
  }
  if (pressed_keys_[Qt::Key_Right]) {
    player_velocity_ += Size(1, 0);
  }
  return player_velocity_;
}

void View::ClearVelocity() {
  player_velocity_ = Size(0, 0);
}

void View::keyReleaseEvent(QKeyEvent* event) {
  pressed_keys_[event->key()] = false;
}

void View::DrawGameObjects(QPainter* painter) {
  controller_->GetPlayer()->GetViewCircle().Draw(painter, &resizer_);
  std::vector<std::shared_ptr<GameObject>>
      drawable_objects = model_->GetDrawableGameObjects();
  for (const auto& object : drawable_objects) {
    if (IsOnTheScreen(object)) {
      object->Draw(painter, &resizer_);
    }
  }
  DrawEndgameMessage(painter);

  button_handler_->SetMainMenuUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetGameUiVisible(true);
}

void View::Resize() {
  resizer_.ChangeSystem(width(), height());
  button_handler_->RescaleButtons(resizer_);
}

void View::resizeEvent(QResizeEvent*) {
  if (!is_model_loaded_) {
    return;
  }
  Resize();
}

void View::UpdateResizer(double radius, const Point& position) {
  resizer_.Update(radius, position);
}

double View::GetViewSize() {
  auto radius = model_->GetPlayer()->GetViewCircle().GetWantedRadius();
  if (pressed_keys_[Qt::Key_E]) {
    radius += constants::kResizerScale;
  }
  if (pressed_keys_[Qt::Key_Q]) {
    radius -= constants::kResizerScale;
  }
  radius = std::min(std::max(radius, constants::kViewCircleMin),
                    constants::kViewCircleMax);
  return radius;
}

bool View::IsOnTheScreen(const std::shared_ptr<GameObject>& object) {
  auto object_pos = object->GetDrawPosition();
  auto screen_rect = this->rect();
  Point top_point = Point(screen_rect.topLeft().x(), screen_rect.topLeft().y());
  auto game_top_point = resizer_.WindowToGameCoordinate(top_point);
  Point bottom_point =
      Point(screen_rect.bottomRight().x(), screen_rect.bottomRight().y());
  auto game_bottom_point = resizer_.WindowToGameCoordinate(bottom_point);

  if (object_pos.GetX() < game_top_point.GetX()
      || object_pos.GetX() > game_bottom_point.GetX()) {
    return false;
  }
  if (object_pos.GetY() < game_top_point.GetY()
      || object_pos.GetY() > game_bottom_point.GetY()) {
    return false;
  }
  return true;
}

void View::DrawMainMenu(QPainter*) {
  // button_handler_->SetSettingsUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
  button_handler_->SetMainMenuUiVisible(true);
}

// void View::DrawSettings(QPainter*) {
//   // button_handler_->SetSettingsUiVisible(true);
//   button_handler_->SetMainMenuUiVisible(false);
// }

void View::DrawPauseMenu(QPainter*) {
  button_handler_->SetGameUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(true);
}

void View::DrawEndgameMessage(QPainter* painter) {

}

void View::EnableGameUi() {
  button_handler_->SetGameUiVisible(true);
}

void View::DisableMainMenuUi() {
  button_handler_->SetMainMenuUiVisible(false);
}

void View::DisableGameUi() {
  button_handler_->SetGameUiVisible(false);
  button_handler_->SetPauseMenuUiVisible(false);
}

void View::EnableMainMenuUi() {
  button_handler_->SetMainMenuUiVisible(true);
}

