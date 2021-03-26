#ifndef PLAYER_H_
#define PLAYER_H_

#include "GameObject/cat.h"
#include <vector>

class Player {
 public:
  Player() = default;
  explicit Player(Cat* cat);
  [[nodiscard]] std::vector<Cat*> GetCats() const;

 private:
  std::vector<Cat*> cats_;
};

#endif  // PLAYER_H_
