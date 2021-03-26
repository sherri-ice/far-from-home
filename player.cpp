#include "player.h"

Player::Player(Cat* cat) {
  cats_.push_back(cat);
}

std::vector<Cat*> Player::GetCats() const {
  return cats_;
}

