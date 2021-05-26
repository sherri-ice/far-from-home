#ifndef GAMEOBJECT_PORTAL_OBJECT_H_
#define GAMEOBJECT_PORTAL_OBJECT_H_

#include <QTimer>

#include "../Model/timer.h"
#include "game_object.h"
#include "../View/progress_bar.h"
#include "../View/result_window.h"
#include "../View/warning.h"

namespace PortalConstants {
const int kMaxSearchTime = 10'000;
const int kMinSearchTime = 1'000;
}

enum class PortalState {
  kDefault,
  kWaitToSearch,
  kSearching,
  kFinishedSearch,
  kWaitToSeeResult,
  kNotificationShown,
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

  bool IsCollected();
  bool IsNotificationShown();
  bool ReadyToShowResult();
  bool HasPortal() const;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;

  void SetIfMessageIsShown(bool is_shown);

  void SetState(PortalState state);

  int GetSearchTime() const;
  void SetSearchTime(int search_time);

  void SetSuperSkin();

  bool IsInArea(int left, int top, int right, int bottom) const;

 private:
  bool has_portal_{false};
  QString skin_path_;
  Timer search_timer_ = Timer(1);
  int search_time_{};
  ProgressBar progress_bar_;
  PortalState state_ = PortalState::kDefault;
  Warning warning_;
  static std::mt19937 random_generator_;
};

#endif  // GAMEOBJECT_PORTAL_OBJECT_H_
