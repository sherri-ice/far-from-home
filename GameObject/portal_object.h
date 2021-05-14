#ifndef GAMEOBJECT_PORTAL_OBJECT_H_
#define GAMEOBJECT_PORTAL_OBJECT_H_

#include <QTimer>
#include "../Model/timer.h"
#include "../View/progress_bar.h"
#include "../View/warning.h"
#include "game_object.h"

enum class PortalState {
  kDefault,
  kSearching,
  kPendingInfo,
  kWaitToSeeResult,
  kCollected
};

class PortalObject : public GameObject {
 public:
  PortalObject(const Size& size,
               const Point& position,
               const QString& skin_path);
  ~PortalObject() = default;

  void SetPortal();
  void RemovePortal();
  void SetSearchState();

  bool IsSearchComplete();
  bool HasPortal() const;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;

  void SetIfMessageIsShown(bool is_shown);
  void SetWaitState();

 private:
  bool has_portal_{true};
  QString skin_path_;
  Timer search_timer_ = Timer(1);
  ProgressBar progress_bar_;
  PortalState state_ = PortalState::kDefault;
  Warning warning_;
};

#endif  // GAMEOBJECT_PORTAL_OBJECT_H_
