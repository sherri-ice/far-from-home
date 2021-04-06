#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QElapsedTimer>
#include <QMainWindow>
#include <QTimer>
#include <map>
#include <memory>

#include "Controller/abstract_controller.h"
#include <Model/model.h>

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(AbstractController* controller, std::shared_ptr<Model> model);
  ~View() override = default;

  Size GetPlayerVelocity();
  void ClearVelocity();

 private:
  int controller_timer_id_;
  QElapsedTimer time_between_ticks_;
  QElapsedTimer view_timer_;

  AbstractController* controller_;
  std::shared_ptr<Model> model_;

  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void timerEvent(QTimerEvent* event) override;

  void DrawMap(QPainter* painter);
  void DrawGameObjects(QPainter* painter);

  Size player_velocity_{Size(0, 0)};
  std::map<Qt::Key, bool> pressed_keys_;
};

#endif  // VIEW_VIEW_H_
