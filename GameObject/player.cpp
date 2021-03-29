#include <memory>
#include "player.h"

Player::Player(const std::shared_ptr<Cat>& cat) {
  cats_.push_back(cat);
}

std::vector<std::shared_ptr<Cat>> Player::GetCats() const {
  return cats_;
}

void Player::OrderCatsToMove(Size velocity) {
  for (auto &cat : cats_) {
    cat->SetVelocityFromPlayer(velocity);
  }
}

