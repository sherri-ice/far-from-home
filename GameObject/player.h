#ifndef GAMEOBJECT_PLAYER_H_
#define GAMEOBJECT_PLAYER_H_

#include <list>
#include <memory>
#include <vector>

#include <Model/timer.h>
#include "GameObject/cat.h"
#include "GameObject/dog.h"
#include "view_circle.h"

class Player {
 public:
  Player() = default;
  explicit Player(const std::shared_ptr<Cat>& cat);
  [[nodiscard]] std::vector<std::shared_ptr<Cat>> GetCats() const;

  void OrderCatsToMove(Size velocity);

  void UpdateDogsAround(std::list<std::shared_ptr<Dog>> dogs);
  void UpdateCatsGroup(const std::list<std::shared_ptr<Cat>>& cats);
  void DismissCats();

  [[nodiscard]] const ViewCircle& GetViewCircle() const;
  void SetViewCircle(const ViewCircle& view_circle);
  [[nodiscard]] const Point& GetPosition() const;

  void Tick(int time);

 private:
  std::vector<std::shared_ptr<Cat>> cats_;
  ViewCircle view_circle_;
  Point position_;

  double visibility_radius_{150};
  double first_group_radious_{60};
  double second_group_radious_{100};
  Timer timer_to_go_home_{1};
};

#endif  // GAMEOBJECT_PLAYER_H_
