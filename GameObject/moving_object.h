#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include <vector>

#include "../GameObject/game_object.h"
#include "../View/animation.h"

namespace constants {
const double kCheckIfVelocityIsCloseToZero = 0.1;
}  // namespace constants

class MovingObject : public GameObject {
 public:
  MovingObject(const Size& size,
               double speed,
               const Point& position = Point(0, 0));
  ~MovingObject() override = default;

  Size GetVelocity() const;

  void Move(int delta_time);
  virtual void SetSpeed(double speed);
  double GetSpeed() const;
  virtual void SetAnimations(std::vector<std::vector<QPixmap>>
                                                  animation = {});
  virtual void IncSpeed(double speed);
  virtual void DecSpeed(double speed);
  virtual void SetVelocity(Size velocity);
  virtual void SetRunAwayDestination(const Point& first_pos,
                                     const Point& second_pos,
                                     const Point& pos,
                                     int x);
  bool IsVelocityChange(Size main_velocity);
  void SetDestination(const Point& destination);

  Size GetDrawSize(const Size& object_size) const override;
  void TickAnimation(int delta_time);
  AnimationState GetAnimationState() const;

  Point GetDestination() const;

 protected:
    Point destination_{};
    bool is_moving_ = false;
    bool was_moving_ = false;
    double speed_;
    Size velocity_;
    static std::mt19937 random_generator_;
    Animation object_animation_;
    bool is_ready_to_be_sent_home = false;
    bool is_ready_to_die = false;

    Size saved_walking_velocity_{};
    bool is_hidding_ = false;
    bool is_back_ = false;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_
