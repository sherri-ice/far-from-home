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
  Point central_cat_position = cats_.at(0)->GetDrawPosition();
  for (auto& dog : dogs) {
    Size distance = central_cat_position.GetVectorTo(dog->GetDrawPosition());
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

const ViewCircle& Player::GetViewCircle() const {
  return view_circle_;
}

void Player::SetViewCircle(const ViewCircle& view_circle) {
  view_circle_ = view_circle;
}

const Point& Player::GetPosition() const {
  return cats_.at(0)->GetDrawPosition();
}

void Player::Tick() {
  view_circle_.Tick();
}

void Player::UpdateStaticObjectsAround(const
  std::list<std::shared_ptr<PortalObject>>& static_objects) {
  Point cat_position;
  Size distance;
  for (const auto& cat : cats_) {
    cat_position = cat->GetRigidPosition();
    for (auto& static_object : static_objects) {
      if (static_object->HasPortal()) {
        distance = cat_position.GetVectorTo(static_object->GetRigidPosition());
        if (distance.GetLength() < visibility_radius_) {
          static_object->SetIfMessageIsShown(true);
        } else {
          static_object->SetIfMessageIsShown(false);
        }
      }
    }
  }
}
