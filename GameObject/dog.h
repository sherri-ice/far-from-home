#ifndef GAMEOBJECT_DOG_H_
#define GAMEOBJECT_DOG_H_

#include "GameObject/moving_object.h"
#include "cat.h"
#include <memory>
#include <vector>

class Dog : public MovingObject {
 public:
  Dog(const Size& size, double speed, const Point& position, double
  visibility_radius);
  ~Dog() override = default;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;
  void Move(int delta_time) override;

  void SetIfItVisibleToPlayer(bool is_visible);
  bool CheckIfCanSeeCat(const Cat* cat) const;
  void SetReachableCat(const std::vector<std::shared_ptr<Cat>>& cats);
  const Cat* GetReachableCat();

 private:
  double visibility_radius_;
  Point home_position_;
  bool is_visible_to_player_{false};
  const Cat* reachable_cat_{nullptr};
};

#endif  // GAMEOBJECT_DOG_H_
