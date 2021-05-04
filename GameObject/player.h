#ifndef GAMEOBJECT_PLAYER_H_
#define GAMEOBJECT_PLAYER_H_

#include <list>
#include <memory>
#include <vector>

#include <Model/timer.h>
#include <Model/group.h>
#include "GameObject/cat.h"
#include "GameObject/dog.h"
#include "view_circle.h"

class Player {
 public:
  Player() = default;
  explicit Player(const std::shared_ptr<Cat>& cat);
  [[nodiscard]] std::vector<std::shared_ptr<Cat>> GetCats() const;

  void OrderCatsToMove(Size velocity_from_player);

  void UpdateDogsAround(std::list<std::shared_ptr<Dog>> dogs);
  void IsReachable(std::list<std::shared_ptr<Dog>> dogs);
  void UpdateCatsGroup(const std::list<std::shared_ptr<Cat>>& cats);
  void DismissCats();
  void GroupTick(int time);

  [[nodiscard]] const ViewCircle& GetViewCircle() const;
  const Group& GetCatGroup() const;
  void SetViewCircle(const ViewCircle& view_circle);
  [[nodiscard]] const Point& GetPosition() const;

  void Tick();

 private:
  std::vector<std::shared_ptr<Cat>> cats_;
  ViewCircle view_circle_;
  Group cat_group_;

  double visibility_radius_{150};

  static std::mt19937 random_generator_;
};

#endif  // GAMEOBJECT_PLAYER_H_
