#ifndef GAMEOBJECT_PLAYER_H_
#define GAMEOBJECT_PLAYER_H_

#include "GameObject/cat.h"
#include "GameObject/dog.h"
#include <vector>
#include <memory>

class Player {
 public:
  Player() = default;
  explicit Player(const std::shared_ptr<Cat>& cat);
  [[nodiscard]] std::vector<std::shared_ptr<Cat>> GetCats() const;

  void OrderCatsToMove(Size velocity);

  void CheckForDogsAround(std::list<std::shared_ptr<Dog>> dogs);

  void DismissCats();

  double GetGroupRadius() const;
  Point GetCentralCatPosition() const;

 private:
  std::vector<std::shared_ptr<Cat>> cats_;
  double visibility_radius_{150};
  double group_radius_{20};
};

#endif  // GAMEOBJECT_PLAYER_H_
