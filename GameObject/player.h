#ifndef GAMEOBJECT_PLAYER_H_
#define GAMEOBJECT_PLAYER_H_

#include "GameObject/cat.h"
#include <vector>
#include <memory>

class Player {
 public:
  Player() = default;
  explicit Player(const std::shared_ptr<Cat>& cat);
  [[nodiscard]] std::vector<std::shared_ptr<Cat>> GetCats() const;

  void OrderCatsToMove(Size velocity);


 private:
  std::vector<std::shared_ptr<Cat>> cats_;
};

#endif  // GAMEOBJECT_PLAYER_H_
