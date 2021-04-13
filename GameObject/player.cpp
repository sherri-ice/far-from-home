#include "player.h"

Player::Player(const std::shared_ptr<Cat>& cat) {
  cats_.push_back(cat);
}

std::vector<std::shared_ptr<Cat>> Player::GetCats() const {
  return cats_;
}

void Player::OrderCatsToMove(Size velocity) {
  for (auto& cat : cats_) {
    cat->SetVelocityFromPlayer(velocity);
  }
}

void Player::UpdateDogsAround(std::list<std::shared_ptr<Dog>> dogs) {
  Point central_cat_position = cats_.at(0)->GetPosition();
  for (auto& dog : dogs) {
    Size distance = central_cat_position.GetVectorTo(dog->GetPosition());
    if (distance.GetLength() < visibility_radius_) {
      dog->SetIfItVisibleToPlayer(true);
    } else {
      dog->SetIfItVisibleToPlayer(false);
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

const ViewCircle& Player::GetViewCircle() const {
  return view_circle_;
}

void Player::SetViewCircle(const ViewCircle& view_circle) {
  view_circle_ = view_circle;
}

const Point& Player::GetPosition() const {
  return cats_.at(0)->GetPosition();
}

void Player::Tick() {
  view_circle_.Tick();
}
