#ifndef VIEW_VIEW_H_
#define VIEW_VIEW_H_

#include <QElapsedTimer>
#include <QMainWindow>
#include <QTimer>
#include <map>
#include <memory>

#include "../Controller/abstract_controller.h"
#include "../Model/model.h"

namespace constants {
const double kFactorForScreen = 0.3;
}  // namespace constants

class View : public QMainWindow {
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

  bool IsOnTheScreen(const std::shared_ptr<GameObject>& object);

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
  void mousePressEvent(QMouseEvent* event) override;

  bool IsOnTheScreen(const std::shared_ptr<GameObject>& object);
  void DrawGameObjects(QPainter* painter);
  void DrawWarnings(QPainter* painter);

  Size player_velocity_;
  std::map<int, bool> pressed_keys_;
  void resizeEvent(QResizeEvent*) override;
};

#endif  // VIEW_VIEW_H_
