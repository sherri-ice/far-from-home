#ifndef PORTAL_OBJECT_H
#define PORTAL_OBJECT_H

#include <QTimer>
#include "game_object.h"

class PortalObject : public GameObject {
 public:
  PortalObject(const Size& size,
               const Point& position,
               const QString& skin_path);
  ~PortalObject() = default;

  bool Search();
  void SetPortal();
  void RemovePortal();

  void Draw(QPainter* painter, Resizer* resizer) const override;


 private:
  bool has_portal_;
  QString skin_path_;
  QTimer search_timer_;
  // QProgressBar

};

#endif //PORTAL_OBJECT_H
