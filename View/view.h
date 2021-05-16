#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QElapsedTimer>
#include <QMainWindow>
#include <QTimer>
#include <map>
#include <memory>

#include "../Controller/abstract_controller.h"
#include "../Model/model.h"
#include "button_handler.h"

class View : public QMainWindow {
 Q_OBJECT

 public:
  explicit View(AbstractController* controller, std::shared_ptr<Model> model);
  ~View() override = default;

  void SecondConstructorPart();

  Size GetPlayerVelocity();
  double GetViewSize();
  void ClearVelocity();
  void Resize();
  void UpdateResizer(double radius, const Point& position);

  void EnableGameUi();
  void DisableMainMenuUi();
  void EnableMainMenuUi();
  void DisableGameUi();

 private:
  int controller_timer_id_;
  QElapsedTimer time_between_ticks_;
  QElapsedTimer view_timer_;
  WindowType window_type_ = WindowType::kMainMenu;
  bool is_model_loaded_ = false;

  AbstractController* controller_;
  Resizer resizer_;
  std::shared_ptr<Model> model_;
  std::shared_ptr<ButtonHandler> button_handler_;

  const QString kEndgameMessage = tr("Restart level or go to the main menu");
  Point message_position_ = Point(constants::kGameWidth / 2, 900);

  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void timerEvent(QTimerEvent* event) override;

  void DrawMainMenu(QPainter* painter);
  // void DrawSettings(QPainter* painter);
  void DrawPauseMenu(QPainter* painter);
  void DrawEndgameMessage(QPainter* painter);

  bool IsOnTheScreen(const std::shared_ptr<GameObject>& object);
  void DrawGameObjects(QPainter* painter);

  Size player_velocity_;
  std::map<int, bool> pressed_keys_;
  void resizeEvent(QResizeEvent*) override;
};

#endif  // VIEW_VIEW_H_
