#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QElapsedTimer>
#include <QMainWindow>
#include <QTimer>
#include <map>

#include "Controller/abstract_controller.h"

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller);
  ~View() override = default;

  Size GetPlayerVelocity();
  void ClearVelocity();

 private:
  int controller_timer_id_;
  QElapsedTimer time_between_ticks_;
  QElapsedTimer view_timer_;
  QTimer player_move_timer_;

  AbstractController* controller_;

  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void timerEvent(QTimerEvent* event) override;

  Size player_velocity_;
  std::map<Qt::Key, bool> pressed_keys_;

  void ClearPressedKeys();
};

#endif  // VIEW_VIEW_H_
