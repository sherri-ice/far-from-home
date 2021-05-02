#ifndef GAMEOBJECT_CAT_H_
#define GAMEOBJECT_CAT_H_

#include "../GameObject/moving_object.h"
#include "../Model/constants.h"

class Cat : public MovingObject {
 public:
  Cat(const Size& size, double speed, const Point& position);
  ~Cat() override = default;

  void Draw(QPainter* painter, Resizer* resizer) const override;
  void Tick(int delta_time) override;

  void SetVelocityFromPlayer(Size velocity);

//  void SetAnimations(std::vector<std::shared_ptr<std::vector<QPixmap>>>
//  animation) override;
};

#endif  // GAMEOBJECT_CAT_H_
