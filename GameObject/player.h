#ifndef GAMEOBJECT_PLAYER_H_
#define GAMEOBJECT_PLAYER_H_

#include "GameObject/cat.h"
#include <vector>

class Player {
 public:
  Player() = default;
  explicit Player(Cat* cat);
  [[nodiscard]] std::vector<Cat*> GetCats() const;

  void OrderCatsToMove(Size velocity);

 private:
  std::vector<Cat*> cats_;
};

#endif  // GAMEOBJECT_PLAYER_H_
