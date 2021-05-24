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
  setFocusPolicy(Qt::StrongFocus);
  layout_ = new QVBoxLayout(this);
  layout_->insertWidget(0, menu_);
  SetWindows();
  show();
}

void View::Pause() {
  // controller_->GetMusicPlayer()->StartMenuMusic();
  menu_->show();
  menu_->Pause();
}

void View::paintEvent(QPaintEvent*) {
  if (menu_->isHidden()) {
    QPainter painter(this);
    DrawGameObjects(&painter);
  }
}

void View::timerEvent(QTimerEvent* event) {
  if (event->timerId() == controller_timer_id_ && menu_->isHidden()) {
    int delta_time = time_between_ticks_.elapsed();
    time_between_ticks_.restart();
    controller_->Tick(controller_->GetCurrentTime() + delta_time);
  }
  repaint();
}

void View::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Space) {
    Pause();
    return;
  }
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
  controller_->GetPlayer()->GetCatGroup().Draw(painter, &resizer_);
  std::vector<std::shared_ptr<GameObject>>
      drawable_objects = model_->GetDrawableGameObjects();
  for (const auto& object : drawable_objects) {
    if (IsOnTheScreen(object)) {
      object->Draw(painter, &resizer_);
    }
  }
}

void View::Resize() {
  resizer_.ChangeSystem(width(), height());
}

void View::resizeEvent(QResizeEvent*) {
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
void View::SetWindows() {
  SetMenuWindow();
  SetSettingsWindow();
  SetPauseWindow();
}

void View::SetMenuWindow() {
  auto start_game_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    time_between_ticks_.start();
    controller_timer_id_ = startTimer(constants::kTimeBetweenTicks);
    view_timer_.start();
    controller_->StartGame();
    menu_->close();
  };
  connect(menu_->GetPlayButton(),
          &QPushButton::released,
          this,
          start_game_button_click);
  auto exit_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    controller_->EndGame();
    close();
  };
  connect(menu_->GetExitButton(),
          &QPushButton::released,
          this,
          exit_button_click);
  // auto sound_button_click = [this]() {
  //   if (is_sound_on_) {
  //     // controller_->GetMusicPlayer()->Pause();
  //     menu_.GetSoundButton()->setIcon( QIcon(":images/menu/buttons/sound_off"
  //                                            ".png"));
  //   } else {
  //     // controller_->GetMusicPlayer()->Resume();
  //     menu_.GetSoundButton()->setIcon( QIcon(
  //         ":images/menu/buttons/sound_on.png"));
  //   }
  // };
  // connect(menu_.GetSoundButton(), &QPushButton::released, this,
  //         sound_button_click);
}
void View::SetPauseWindow() {
  auto resume_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    menu_->close();
  };
  connect(menu_->GetResumeButton(), &QPushButton::released, this,
          resume_button_click);
  auto restart_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    controller_->EndGame();
    controller_->StartGame();
    menu_->close();
  };
  connect(menu_->GetRestartButton(), &QPushButton::released, this,
          restart_button_click);
  auto menu_button_click = [this]() {
    controller_->GetMusicPlayer()->PlayButtonSound();
    menu_->MainMenu();
    controller_->EndGame();
  };
  connect(menu_->GetMenuButton(), &QPushButton::released, this,
          menu_button_click);
}

void View::SetSettingsWindow() {
}





