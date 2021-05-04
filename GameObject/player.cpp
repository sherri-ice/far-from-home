#include <iostream>
#include "player.h"

std::mt19937 Player::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());


Player::Player(const std::shared_ptr<Cat>& cat) : cat_group_(100, 150) {
  cats_.push_back(cat);
}

std::vector<std::shared_ptr<Cat>> Player::GetCats() const {
  return cats_;
}

void Player::OrderCatsToMove(Size velocity_from_player) {
  cat_group_.velocity_ = velocity_from_player;
  double vector_to_group;
  std::uniform_real_distribution<> velocity(-1, 1);
  std::uniform_int_distribution<> x_destination
      (cat_group_.central_position_.GetX() - cat_group_.first_radius_,
       cat_group_.central_position_.GetX() + cat_group_.first_radius_);
  std::uniform_int_distribution<> y_destination
      (cat_group_.central_position_.GetY() - cat_group_.first_radius_ *
           constants::kSemiMinorCoefficient,
       cat_group_.central_position_.GetY() + cat_group_.first_radius_ *
           constants::kSemiMinorCoefficient);

  for (auto cat : cats_) {
    if (cat == cats_[0] && cat->GetCatState() != CatState::kIsDoingSomething) {
      cat->SetCatState(CatState::kIsMainCat);
      cat->SetVelocity(velocity_from_player);
      continue;
    }
    vector_to_group = cat_group_.central_position_.
        GetVectorTo(cat->GetDrawPosition()).GetLength();

    if (vector_to_group < cat_group_.first_radius_) {
      if (velocity_from_player == Size(0, 0)) {
        if (cat->GetCatState() == CatState::kIsFollowingPlayer) {
          cat->SetCatState(CatState::kIsResting);
          cat->SetHomePosition(cat->GetDrawPosition());
          cat->SetVelocity(velocity_from_player);
        }
      } else {
        if (cat->GetTimer().IsTimeOut(static_cast<int>
        (CatState::kIsFollowingPlayer))
            || !(cat->GetTimer().IsActive(static_cast<int>
            (CatState::kIsFollowingPlayer)))) {
          cat->SetVelocity(velocity_from_player);
          cat->SetCatState(CatState::kIsFollowingPlayer);
        }
      }
    } else if (vector_to_group < cat_group_.second_radius_) {
      if (cat->GetCatState() != CatState::kIsComingDestination) {
        cat->SetCatState(CatState::kIsComingDestination);
        auto destination = Point(x_destination(random_generator_),
                                 y_destination(random_generator_));
        cat->SetDestination(destination);
      }
    } else {
        cat->SetIsInGroup(false);
        if (cat->GetIsReachable()) {
          cat->SetIsReachable(false);
          cat->DecSpeed(constants::kCatRunCoefficient);
        }
        cat->SetCatState(CatState::kIsResting);
        cat->SetVelocity(Size(0, 0));
        cat_group_.DecGroup();
    }

    cats_.erase(std::remove_if(cats_.begin(), cats_.end(),
      [](const std::shared_ptr<Cat>& cat){return !(cat->GetIsInGroup());}),
              cats_.end());
  }
}

void Player::UpdateDogsAround(std::list<std::shared_ptr<Dog>> dogs) {
  Point central_cat_position = cat_group_.central_position_;
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
  cat_group_.central_position_ = Point(0, 0);
  std::uniform_int_distribution<> x_destination
      (cat_group_.central_position_.GetX() - 1000,
       cat_group_.central_position_.GetX() + 1000);
  std::uniform_int_distribution<> y_destination
      (cat_group_.central_position_.GetY() - 1000,
       cat_group_.central_position_.GetY() + 1000);

  for (size_t i = 1; i < cats_.size(); i++) {
    cats_.at(i)->SetIsInGroup(false);
    if (cats_.at(i)->GetIsReachable()) {
      cats_.at(i)->SetIsReachable(false);
      cats_.at(i)->DecSpeed(constants::kCatRunCoefficient);
    }
    cats_.at(i)->SetDestination(Point(x_destination(random_generator_),
                                      y_destination(random_generator_)));
    cats_.at(i)->SetCatState(CatState::kIsComingDestination);
  }
  cat_group_.DecGroup(cats_.size() - 1);
  cats_.erase(cats_.cbegin() + 1, cats_.cend());
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

void Player::UpdateCatsGroup(const std::list<std::shared_ptr<Cat>>& cats) {
  for (auto& cat : cats_) {
    for (auto& wild_cat : cats) {
      if (cat == wild_cat) {
        continue;
      }
      auto length = cat_group_.central_position_.
          GetVectorTo(wild_cat->GetDrawPosition()).GetLength();
      if (length < cat_group_.first_radius_ &&
          !(wild_cat->GetIsInGroup())) {
        cats_.push_back(wild_cat);
        wild_cat->SetIsInGroup(true);
        wild_cat->SetCatState(CatState::kIsFollowingPlayer);
        cat_group_.IncGroup();
      }
    }
  }
}

void Player::IsReachable(std::list<std::shared_ptr<Dog>> dogs) {
  for (auto cat : cats_) {
    bool is_reachable{false};
    for (auto dog : dogs) {
      if (&(*cat) == dog->GetReachableCat()) {
        if (!cat->GetIsReachable()) {
          cat->SetIsReachable(true);
          cat->IncSpeed(constants::kCatRunCoefficient);
        }
        is_reachable = true;
      }
    }
    if (!is_reachable) {
      if (cat->GetIsReachable()) {
        cat->DecSpeed(constants::kCatRunCoefficient);
      }
      cat->SetIsReachable(false);
    }
  }
}

const Group& Player::GetCatGroup() const {
  return cat_group_;
}

void Player::GroupTick(int time) {
  cat_group_.SetSpeed(cats_.at(0)->GetSpeed());
  cat_group_.Tick(time);
  cat_group_.Move(time);
}
