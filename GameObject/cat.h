#ifndef GAMEOBJECT_CAT_H_
#define GAMEOBJECT_CAT_H_

#include <memory>

#include "GameObject/moving_object.h"
#include "Model/constants.h"

class Cat : public MovingObject {
 public:
  Cat(const Size& size, double speed, const Point& position);
  ~Cat() override = default;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int time) override;

  void SetVelocityFromPlayer(Size velocity);
  bool GetIsInGroup() const;
  Point GetHomePosition() const;
  void SetIsInGroup(bool);

  void RepulsivePower(std::shared_ptr<Cat> object);

 private:
  bool is_in_group_{false};
  Point home_position_;
};

#endif  // GAMEOBJECT_CAT_H_
