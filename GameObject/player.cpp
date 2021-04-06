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

const ViewCircle& Player::GetViewCircle() const {
  return view_circle_;
}

void Player::SetViewCircle(const ViewCircle& view_circle) {
  view_circle_ = view_circle;
}

const Point& Player::GetPosition() const {
  return cats_.at(0)->GetPosition();
}
