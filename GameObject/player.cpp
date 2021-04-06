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

void Player::CheckForDogsAround(std::list<std::shared_ptr<Dog>> dogs) {
  Point central_cat_position = cats_.at(0)->GetPosition();
  for (auto &dog : dogs) {
    Size distance = central_cat_position.GetVectorTo(dog->GetPosition());
    if (distance.GetLength() < visibility_radius_ ||
        std::abs(distance.GetLength() - visibility_radius_) <=
        constants::kEpsilon) {
      dog->SetIfIsVisibleToPlayer(true);
    } else {
      dog->SetIfIsVisibleToPlayer(false);
    }
  }
}

void Player::DismissCats() {
  cats_.at(0)->SetPosition(Point(0, 0));
}

double Player::GetGroupRadius() const {
  return group_radius_;
}

Point Player::GetCentralCatPosition() const {
  return cats_.at(0)->GetPosition();
}
