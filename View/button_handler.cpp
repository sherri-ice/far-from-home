#include "button_handler.h"

ButtonHandler::ButtonHandler(QMainWindow* main_window,
                             AbstractController* controller)
    : QObject(main_window), main_window_(main_window), controller_(controller) {
  CreateButtons();
  QSettings settings;


  // for sounds
  // SetSoundOn(settings.value("sound_on", true).toBool());

  //for full screen button
  bool is_fullscreen = settings.value("fullscreen", true).toBool();
  is_fullscreen_ = is_fullscreen;
  // fullscreen_button_->setText(
  //     is_fullscreen ? tr("WINDOWED MODE") : tr("FULLSCREEN MODE"));


  window_type_ = WindowType::kMainMenu;
}

void ButtonHandler::CreateButtons() {
  CreateMainMenuButtons();
  CreateGameButtons();
  CreatePauseMenuButtons();
  // CreateSettingsButtons();
}


void ButtonHandler::RescaleButtons(const Resizer& size_handler) {
  ChangeFirstButtonCoordinates(Point(main_window_->width()/ 2,
                               0));
  std::cout << main_window_->width() << " " << main_window_->height() << "\n";
  RescaleMainMenuButtons(size_handler);
  RescaleGameButtons(size_handler);
  RescalePauseMenuButtons(size_handler);
  // RescaleSettingsButtons(size_handler);
}

void ButtonHandler::SetMainMenuUiVisible(bool visible) {
  start_game_button_->setVisible(visible);
  exit_button_->setVisible(visible);
  // settings_button_->setVisible(visible);
}

// void ButtonHandler::SetSettingsUiVisible(bool visible) {
//   // sound_button_->setVisible(visible);
//   to_main_menu_button_->setVisible(visible);
//   fullscreen_button_->setVisible(false);
// }

void ButtonHandler::SetGameUiVisible(bool visible) {
  pause_button_->setVisible(visible);
}

void ButtonHandler::SetPauseMenuUiVisible(bool visible) {
  continue_button_->setVisible(visible);
  restart_button_->setVisible(visible);
  to_menu_from_pause->setVisible(visible);
}

WindowType ButtonHandler::GetWindowType() const {
  return window_type_;
}

void ButtonHandler::CreateMainMenuButtons() {
  start_game_button_ = new Button(
      large_button_size_, main_window_,
      "../images/buttons/start.png",
      "../images/buttons/start_1.png");
  auto start_game_button_click = [this]() {
    // controller_->GetMusicPlayer()->PlayButtonSound();
    window_type_ = WindowType::kGame;
    controller_->StartGame();
  };
  connect(start_game_button_, &QPushButton::clicked, start_game_button_click);

  // settings_button_ = new Button(
  //     small_button_size_, main_window_,
  //     "../images/buttons/next.png",
  //     "../images/buttons/next_1.png");
  // auto settings_button_click = [this]() {
  //   // controller_->GetMusicPlayer()->PlayButtonSound();
  //   window_type_ = WindowType::kSettings;
  // };
  // connect(settings_button_, &QPushButton::clicked, settings_button_click);

  exit_button_ = new Button(
      small_button_size_, main_window_,
      "../images/buttons/back.png",
      "../images/buttons/back_1.png");
  connect(
      exit_button_, &QPushButton::clicked, main_window_, &QMainWindow::close);
  SetMainMenuUiVisible(false);
}

void ButtonHandler::RescaleMainMenuButtons(Resizer size_handler) {
  Size shift = Size(0, small_button_size_.GetHeight());

  start_game_button_->SetGeometry(first_button_coordinate_,
                                  size_handler);
  // settings_button_->SetGeometry(first_button_coordinate_ + shift * 2,
  //                               size_handler);
  exit_button_->SetGeometry(first_button_coordinate_ + shift * 3,
                            size_handler);
}

// void ButtonHandler::CreateSettingsButtons() {
//   QSettings settings;
//   // sound_button_ = new Button(
//   //     button_size_, main_window_,
//   //     ":resources/buttons_resources/inc_level_button.png",
//   //     ":resources/buttons_resources/inc_level_button_active.png");
//   //
//   // auto sound_button_click = [this]() {
//   //   QSettings settings(constants::kApplicationName);
//   //   // controller_->GetMusicPlayer()->PlayButtonSound();
//   //   SetSoundOn(!is_sound_on_);
//   //   settings.setValue("sound_on", is_sound_on_);
//   // };
//   // connect(sound_button_, &QPushButton::clicked, sound_button_click);
//
//   fullscreen_button_ = new Button(
//       small_button_size_, main_window_,
//       "../images/cat/down/Frame 0.png",
//       "../images/cat/down/Frame 1.png");
//   auto fullscreen_click = [this]() {
//     QSettings settings;
//     // controller_->GetMusicPlayer()->PlayButtonSound();
//     SetFullscreen(!is_fullscreen_);
//     settings.setValue("fullscreen", is_fullscreen_);
//   };
//   connect(fullscreen_button_, &QPushButton::clicked, fullscreen_click);
//
//   to_main_menu_button_ = new Button(
//       small_button_size_, main_window_,
//       "../images/buttons/back.png",
//       "../images/buttons/back_1.png");
//   auto back_to_main_menu_click = [this]() {
//     // controller_->GetMusicPlayer()->PlayButtonSound();
//     window_type_ = WindowType::kMainMenu;
//   };
//   connect(to_main_menu_button_, &QPushButton::clicked, back_to_main_menu_click);
//   SetSettingsUiVisible(false);
// }

// void ButtonHandler::RescaleSettingsButtons(Resizer size_handler) {
//   Size shift = Size(0, large_button_size_.GetHeight() + shift_);
//   auto first_button_coordinate = Point(
//       first_button_coordinate_.GetX(),
//       first_button_coordinate_.GetX() - shift_ - large_button_size_.GetHeight());
//   // sound_button_->SetGeometry(
//   //     first_button_coordinate + Size(long_button_size_.width / 2, 0)
//   //         - Size(short_button_size_.width, 0), size_handler);
//   Size temp_shift{};
//   to_main_menu_button_->SetGeometry(first_button_coordinate + shift * 3, size_handler);
// }

void ButtonHandler::CreateGameButtons() {
  pause_button_ = new Button(
      small_button_size_ / 2, main_window_,
      "../images/buttons/pause.png",
      "../images/buttons/pause_1.png");
  auto pause_button_click = [this]() {
    // controller_->GetMusicPlayer()->PlayButtonSound();
    window_type_ = WindowType::kPauseMenu;
  };

  connect(pause_button_, &QPushButton::clicked, pause_button_click);

  SetGameUiVisible(false);
}

void ButtonHandler::RescaleGameButtons(Resizer size_handler) {
  pause_button_->SetGeometry(
      Point(main_window_->width() - small_button_size_.GetWidth() - shift_,
            shift_),
      size_handler);

}

void ButtonHandler::CreatePauseMenuButtons() {
  // todo restart button doesnt work
  restart_button_ = new Button(
      small_button_size_, main_window_,
      "../images/buttons/start.png",
      "../images/buttons/start_1.png");
  auto restart_button_click = [this]() {
    // controller_->GetMusicPlayer()->PlayButtonSound();
    window_type_ = WindowType::kGame;
    controller_->EndGame();
    controller_->StartGame();
  };
  connect(restart_button_, &QPushButton::clicked, restart_button_click);

  continue_button_ = new Button(
      large_button_size_, main_window_,
      "../images/buttons/play.png",
      "../images/buttons/play_1.png");
  auto continue_button_click = [this]() {
    // controller_->GetMusicPlayer()->PlayButtonSound();
    window_type_ = WindowType::kGame;
  };
  connect(continue_button_, &QPushButton::clicked, continue_button_click);

  to_menu_from_pause = new Button(
      small_button_size_, main_window_,
      "../images/buttons/back.png",
      "../images/buttons/back_1.png");
  auto from_pause_click = [this]() {
    // controller_->GetMusicPlayer()->PlayButtonSound();
    // controller_->GetMusicPlayer()->StopNewLevelSound();
    window_type_ = WindowType::kMainMenu;
    controller_->EndGame();
  };
  connect(to_menu_from_pause, &QPushButton::clicked, from_pause_click);
  SetGameUiVisible(false);
}

void ButtonHandler::RescalePauseMenuButtons(Resizer size_handler) {
  Size shift = Size(0, small_button_size_.GetHeight() + shift_);
  continue_button_->SetGeometry(first_button_coordinate_, size_handler);
  restart_button_->SetGeometry(first_button_coordinate_ + shift, size_handler);
  to_menu_from_pause->SetGeometry(first_button_coordinate_ + shift * 2,
                                  size_handler);
}

//
// void ButtonHandler::SetSoundOn(bool sound_on) {
//   is_sound_on_ = sound_on;
//   sound_button_->EnableSecondIcon(!is_sound_on_);
//   controller_->SetGameVolume(100 * static_cast<int>(is_sound_on_));
// }
//
// int ButtonHandler::GetCurrentLevel() const {
//   return level_number_;
// }

void ButtonHandler::SetWindowType(WindowType window_type) {
  window_type_ = window_type;
}

// void ButtonHandler::SetFullscreen(bool fullscreen) {
//   if (is_fullscreen_ == fullscreen) {
//     return;
//   }
//   is_fullscreen_ = fullscreen;
//   fullscreen_button_->setText(
//       fullscreen ? tr("WINDOWED MODE") : tr("FULLSCREEN MODE"));
//   main_window_->hide();
//
//   if (fullscreen) {
//     main_window_->showFullScreen();
//   } else {
//     main_window_->showNormal();
//   }
// }

void ButtonHandler::ChangeFirstButtonCoordinates(const Point& point) {
  first_button_coordinate_ = point;
}

