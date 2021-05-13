#ifndef GAMEOBJECT_MOVING_OBJECT_H_
#define GAMEOBJECT_MOVING_OBJECT_H_

#include "../GameObject/game_object.h"
#include "../View/animation.h"
#include <vector>

class MovingObject : public GameObject {
 public:
    MovingObject(const Size& size,
                 double speed,
                 const Point& position = Point(0, 0));
    ~MovingObject() override = default;
    void Move(int delta_time);

    virtual void SetSpeed(double speed);
    double GetSpeed() const;
    [[nodiscard]] AnimationState GetAnimation() const;
    virtual void SetAnimations(std::vector<std::vector<QPixmap>>
                                                  animation = {});
  virtual void IncSpeed(double speed);
  virtual void DecSpeed(double speed);
  virtual void SetVelocity(Size velocity);
  virtual void SetRunAwayDestination(const Point& first_pos,
                                     const Point& second_pos,
                                     const Point& pos,
                                     int x);
  virtual double GetSpeed();
  bool IsVelocityChange(Size main_velocity);
  void SetDestination(const Point& destination);

 protected:
    Point destination_{};
    bool is_moving_ = false;
    bool was_moving_ = false;
    double speed_;
    Size velocity_;
    static std::mt19937 random_generator_;
    Animation object_animation_;
};

#endif  // GAMEOBJECT_MOVING_OBJECT_H_
