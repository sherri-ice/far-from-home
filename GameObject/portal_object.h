#ifndef GAMEOBJECT_PORTAL_OBJECT_H_
#define GAMEOBJECT_PORTAL_OBJECT_H_

#include <QTimer>
#include <Model/timer.h>
#include <View/progress_bar.h>
#include "game_object.h"

class PortalObject : public GameObject {
 public:
  PortalObject(const Size& size,
               const Point& position,
               const QString& skin_path);
  ~PortalObject() = default;

  void SetPortal();
  void RemovePortal();
  void SetSearchState();
  void SetDefaultState();

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;

 private:
  bool has_portal_;
  QString skin_path_;
  Timer search_timer_ = Timer(1);
  ProgressBar progress_bar_;
  bool is_searching_ = false;
};

#endif  // GAMEOBJECT_PORTAL_OBJECT_H_
