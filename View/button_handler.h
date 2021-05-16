#ifndef VIEW_BUTTON_HANDLER_H_
#define VIEW_BUTTON_HANDLER_H_

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QSettings>
#include <QTranslator>

#include <algorithm>

#include "../Controller/abstract_controller.h"
#include "button.h"
#include "resizer.h"

class ButtonHandler : public QObject {
 Q_OBJECT

 public:
  ButtonHandler(QMainWindow* main_window, AbstractController* controller);
  ~ButtonHandler() override = default;

  void CreateButtons();
  // void UpdateButtonsStatus(bool online_status, bool register_status);

  void RescaleButtons(const Resizer& size_handler);
  void SetMainMenuUiVisible(bool visible);
  // void SetSettingsUiVisible(bool visible);
  void SetGameUiVisible(bool visible);
  void SetPauseMenuUiVisible(bool visible);
  void ChangeFirstButtonCoordinates(const Point& point);

  // void SetTitlesVisible(bool visible);
  WindowType GetWindowType() const;

  void SetWindowType(WindowType type);

  // int GetMaxLevel() const;
 private:
  // creating main menu
  void CreateMainMenuButtons();
  void RescaleMainMenuButtons(Resizer size_handler);
  // creating settings
  // void CreateSettingsButtons();
  // void RescaleSettingsButtons(Resizer size_handler);
  // creating game window
  void CreateGameButtons();
  void RescaleGameButtons(Resizer size_handler);
  // creating pause menu
  void CreatePauseMenuButtons();
  void RescalePauseMenuButtons(Resizer size_handler);

  // void SetSoundOn(bool sound_on);
  // void SetFullscreen(bool fullscreen);
 private:
  QMainWindow* main_window_;
  WindowType window_type_ = WindowType::kMainMenu;

  AbstractController* controller_;
  Button* start_game_button_;
  // Button* settings_button_;
  Button* exit_button_;

  Button* pause_button_;

  // Button* sound_button_;
  // Button* fullscreen_button_;


  // Button* titles_button_;
  Button* to_main_menu_button_;


  Button* to_settings_button_;
  Button* continue_button_;
  Button* restart_button_;

  Button* to_menu_from_pause;

  Size small_button_size_ = Size(355, 100);
  Size large_button_size_ = Size(710, 200);
  Point first_button_coordinate_ = Point(0, 0);
  int shift_ = 20;
  // bool is_sound_on_ = true;
  bool is_fullscreen_ = true;
};

#endif  // VIEW_BUTTON_HANDLER_H_
