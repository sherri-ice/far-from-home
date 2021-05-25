#ifndef GAMEOBJECT_CAT_H_
#define GAMEOBJECT_CAT_H_

#include <memory>
#include <random>

#include "../GameObject/moving_object.h"
#include "../Model/constants.h"
#include "../Model/timer.h"

namespace constants {
const int kTimeToRestMin = 1000;
const int kTimeToRestMax = 1800;
const int kTimeToWalkMin = 800;
const int kTimeToWalkMax = 1000;
const int kTimeToFollowMin = 500;
const int kTimeToFollowMax = 1000;
const int kTimeToCommingDestinationMin = 1000;
const int kTimeToCommingDestinationMax = 1500;
const int kTimesToChangeDirectionMin = 2;
const int kTimesToChangeDirectionsMax = 5;
}  // namespace constants

enum class CatState {
  kIsResting,
  kIsWalking,
  kIsFollowingPlayer,
  kIsComingDestination,
  kIsMainCat,
  kIsSearching,
  kIsGoingToSearch,
  kHasFinishedSearching,
  kNeedsToBeSendHome,
  kReadyToBeDeleted,
  SIZE
};

class Cat : public MovingObject {
 public:
  Cat(const Size& size, double speed, const Point& position);
  ~Cat() override = default;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;

  bool GetIsInGroup() const;
  void SetHomePosition(const Point& position);
  void SetIsInGroup(bool);
  void SetIsReachable(bool);

  void SetCatState(CatState cat_state);
  CatState GetCatState();
  bool GetIsReachable();

  Timer GetTimer();
  int GetSearchingTime() const;
  void SetSearchingTime(int searching_time);

 private:
  bool is_in_group_{false};
  bool is_reachable_cat_{false};
  bool came_back_to_player = true;
  Point home_position_;
  CatState cat_state_{CatState::kIsResting};
  int change_directions_count_{0};
  Timer timers_;
  int searching_time_{1000};
  int time_for_cats_homesending_{1000};

  static std::mt19937 random_generator_;
};

#endif  // GAMEOBJECT_CAT_H_
