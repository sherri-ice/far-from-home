#ifndef GAMEOBJECT_DOG_H_
#define GAMEOBJECT_DOG_H_

#include <memory>
#include <random>
#include <vector>

#include "GameObject/cat.h"
#include "GameObject/moving_object.h"
#include "Model/timer.h"

enum class DogState {
  kIsResting,
  kIsWalking,
  kChasingCat,
  kIsComingHome
};

class Dog : public MovingObject {
 public:
  Dog(const Size& size, double speed, const Point& position, double
  visibility_radius, double walking_speed);
  ~Dog() override = default;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;
  void Move(int delta_time) override;

  void SetIfItVisibleToPlayer(bool is_visible);
  bool CheckIfCanSeeCat(const Cat* cat) const;
  void SetReachableCat(const std::vector<std::shared_ptr<Cat>>& cats);

  void StartTimer();
  void ChangeVelocity();

 private:
  Point home_position_;
  double visibility_radius_;
  bool is_visible_to_player_{false};
  const Cat* reachable_cat_{nullptr};
  DogState dog_state_{DogState::kIsResting};
  int change_directions_count_{0};
  double walking_speed_;
  Timer timer_to_walk_;
  static std::mt19937 random_generator_;

  void TimeOut();
};

#endif  // GAMEOBJECT_DOG_H_
