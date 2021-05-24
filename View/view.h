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
 private:
  int controller_timer_id_;
  QElapsedTimer time_between_ticks_;
  QElapsedTimer view_timer_;

  AbstractController* controller_;
  Resizer resizer_;
  std::shared_ptr<Model> model_;

  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void timerEvent(QTimerEvent* event) override;
  void focusOutEvent(QFocusEvent* event) override;
  void focusInEvent(QFocusEvent* event) override;

  bool IsOnTheScreen(const std::shared_ptr<GameObject>& object);
  void DrawGameObjects(QPainter* painter);

  void Pause();
  void SetWindows();
  void SetMenuWindow();
  void SetSettingsWindow();
  void SetPauseWindow();

  void MakeBlur();

  Size player_velocity_;
  std::map<int, bool> pressed_keys_;
  void resizeEvent(QResizeEvent*) override;
  Menu* menu_ = new Menu(this);
  bool is_sound_on_ = true;
  QHBoxLayout layout_;
};

#endif  // VIEW_VIEW_H_
