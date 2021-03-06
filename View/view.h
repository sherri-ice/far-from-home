#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QElapsedTimer>
#include <QMainWindow>
#include <QTimer>
#include <map>
#include <memory>
#include <QStackedWidget>
#include <QLayout>

#include "../Controller/abstract_controller.h"
#include "../Model/model.h"
#include "menu.h"
#include "background.h"
#include "deathwindow.h"
#include "win_window.h"

namespace constants {
const double kFactorForScreen = 0.3;
}  // namespace constants

class View : public QWidget {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller, std::shared_ptr<Model> model);
  ~View() override = default;

  Size GetPlayerVelocity();
  double GetViewSize();
  void ClearVelocity();
  void Resize();
  void UpdateResizer(double radius, const Point& position);

  Point GetCoordinatesForWarning() const;
  double GetWidthOfScreenAsGame() const;
  double GetHeightOfScreeAsGame()
  const;

  bool IsOnTheScreen(const std::shared_ptr<GameObject>& object);

  void ShowResultWindow(bool is_found);
  ResultWindow& GetResultWindow();

  void ShowDeathWindow();
  DeathWindow* GetDeathWindow();

  void ShowWinWindow();
  WinWindow* GetWinWindow();

 private:
  int controller_timer_id_;
  QElapsedTimer time_between_ticks_;
  QElapsedTimer view_timer_;

  AbstractController* controller_;
  Resizer resizer_{};
  std::shared_ptr<Model> model_;

  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void timerEvent(QTimerEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

  void DrawGameObjects(QPainter* painter);
  void DrawWarnings(QPainter* painter);

  void Pause();
  void SetWindows();
  void SetMenuWindow();
  void SetSettingsWindow();
  void SetPauseWindow();
  void SetDeathWindow();
  void SetWinWindow();


  Size player_velocity_;
  std::map<int, bool> pressed_keys_;
  void resizeEvent(QResizeEvent*) override;
  Menu* menu_ = new Menu(this);
  bool is_sound_on_ = true;
  QVBoxLayout* layout_;

  ResultWindow result_window_;
  DeathWindow* death_window_ = new DeathWindow(this);
  WinWindow* win_window_ = new WinWindow(this);
  Background background_;
};

#endif  // VIEW_VIEW_H_
