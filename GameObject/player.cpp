#include "player.h"

Player::Player(Cat* cat) {
  cats_.push_back(cat);
}

std::vector<Cat*> Player::GetCats() const {
  return cats_;
}

void Player::OrderCatsToMove(Size velocity) {
  for (auto &cat : cats_) {
    cat->SetVelocityFromPlayer(velocity);
  }
}
