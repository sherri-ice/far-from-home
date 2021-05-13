#ifndef GAMEOBJECT_DOG_H_
#define GAMEOBJECT_DOG_H_

#include "cat.h"
#include <memory>
#include <random>
#include <vector>

#include "../GameObject/cat.h"
#include "../Model/timer.h"
#include "../GameObject/moving_object.h"

namespace dog_constants {
const int kTimeToRestMin = 5000;
const int kTimeToRestMax = 7000;
const int kTimeToWalkMin = 1500;
const int kTimeToWalkMax = 3500;
const int kTimeToComeHomeMin = 1000;
const int kTimeToComeHomeMax = 2000;
const int kTimesToChangeDirectionMin = 2;
const int kTimesToChangeDirectionsMax = 5;
}  // namespace dog_constants

enum class DogState {
  kIsResting,
  kIsWalking,
  kChasingCat,
  kIsComingHome,
  SIZE
};

class Dog : public MovingObject {
 public:
  Dog(const Size& size, double speed, const Point& position, double
  visibility_radius, double walking_speed);
  ~Dog() override = default;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;

  void SetIfItVisibleToPlayer(bool is_visible);
  bool CheckIfCanSeeCat(const Cat* cat) const;
  void SetReachableCat(const std::vector<std::shared_ptr<Cat>>& cats);
  const Cat* GetReachableCat();


  double GetVisibilityRadius() const;
  double GetWalkingSpeed() const;
  void SetIsMainCatCaught(bool);

 private:
  Point home_position_;
  double visibility_radius_;
  bool is_visible_to_player_{false};
  const Cat* reachable_cat_{nullptr};
  DogState dog_state_{DogState::kIsResting};
  int change_directions_count_{0};
  double walking_speed_;
  Timer timers_;
  bool is_main_cat_caught_{false};

  static std::mt19937 random_generator_;
};

#endif  // GAMEOBJECT_DOG_H_
