#ifndef GAMEOBJECT_DOG_H_
#define GAMEOBJECT_DOG_H_

#include "GameObject/target_moving_object.h"

class Dog : public TargetMovingObject {
 public:
  Dog(const Size& size, double speed, const Point& position, double
  visibility_radius);
  ~Dog() override = default;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;
  void Move(int delta_time) override;

  void UpdateDogsAround(bool is_visible);
  bool CheckIfCanSeePlayer(const Point& player_position, double group_radius);
  Point GetHomePosition() const;

 private:
  double visibility_radius_;
  Point home_position_;
  bool is_visible_to_player_{false};
};

#endif  // GAMEOBJECT_DOG_H_
