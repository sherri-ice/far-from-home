#ifndef MODEL_PLAYER_H_
#define MODEL_PLAYER_H_

#include "GameObject/cat.h"

class Player : public MovingObject {
 public:
  Player(Size size, double speed, const Point& position);
  ~Player() override = default;

  void SetPosition(const Point& position) override;
  void Move(int time) override;
  void Tick(int time) override;
  void Draw(QPainter* painter) override;

  void SetSpeed(double speed) override;
  void SetVelocity(Size velocity) override;

 private:
  std::vector<Cat> cats_;

  void SetPositionForEachCat();
};

#endif  // MODEL_PLAYER_H_
