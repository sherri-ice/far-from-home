#include "player.h"

std::mt19937 Player::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

Player::Player(const std::shared_ptr<Cat>& cat) : cat_group_(60, 150) {
  cats_.emplace_back(cat);
  food_saturation_ = cat->GetFoodSaturation();
  speed_of_hunger_ = constants::kSpeedOfHunger;
}

std::vector<std::shared_ptr<Cat>> Player::GetCats() const {
  return cats_;
}

void Player::OrderCatsToMove(Size velocity_from_player) {
  cat_group_.velocity_ = velocity_from_player;
  Point cat_position;
  std::uniform_real_distribution<> velocity(-1, 1);

  for (auto& cat : cats_) {
    if (cat == GetMainCat()) {
      cat->SetCatState(CatState::kIsMainCat);
      cat->SetVelocity(velocity_from_player);
      continue;
    }
    if (cat->GetCatState() == CatState::kIsGoingToSearch || cat->GetCatState
        () == CatState::kIsSearching || cat->GetCatState() ==
        CatState::kNeedsToBeSendHome || cat->GetCatState() ==
        CatState::kReadyToBeDeleted) {
      continue;
    }
    if (cat->GetCatState() == CatState::kHasFinishedSearching) {
      cat->SetDestination(cats_.at(0)->GetDrawPosition() + Point(20, 50));
      cat->SetDestinationRect(cats_.at(0)->GetRigidBody()->GetRect());
      free_cats_.push_back(cat);
      continue;
    }
    cat_position = cat->GetRigidPosition();

    if (cat_position.IsInEllipse(cat_group_.central_position_,
                                 cat_group_.first_radius_)) {
      if (velocity_from_player == Size(0, 0)) {
        if (cat->GetCatState() == CatState::kIsFollowingPlayer) {
          cat->SetCatState(CatState::kIsResting);
          cat->SetHomePosition(cat->GetRigidPosition());
          cat->SetVelocity(velocity_from_player);
        }
      } else {
        if (cat->GetTimer().IsTimeOut(static_cast<int>
                                      (CatState::kIsFollowingPlayer))
            || !(cat->GetTimer().IsActive(static_cast<int>
                                          (CatState::kIsFollowingPlayer)) ||
                (cat->IsVelocityChange(velocity_from_player))) &&
                (cat->GetCatState() != CatState::kNeedsToBeSendHome)) {
          cat->SetVelocity(velocity_from_player);
          cat->SetCatState(CatState::kIsFollowingPlayer);
        }
      }
    } else if (cat_position.IsInEllipse(cat_group_.central_position_,
                                        cat_group_.second_radius_)) {
      if (cat->GetCatState() != CatState::kIsComingDestination) {
        cat->SetCatState(CatState::kIsComingDestination);
        auto destination = GenerateRandomDestination();
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
  }

  for (const auto& cat : cats_) {
    if (!cat->GetIsInGroup()) {
      max_food_saturation_ -= constants::kMaxFoodSaturation;
      speed_of_hunger_ -= constants::kSpeedOfHunger;
      double part_of_food_saturation = food_saturation_ / cats_.size();
      food_saturation_ -= part_of_food_saturation;
      cat->SetFoodSaturation(part_of_food_saturation);
    }
  }

  cats_.erase(std::remove_if(cats_.begin(), cats_.end(),
                             [](const std::shared_ptr<Cat>& cat) {
                               return !(cat->GetIsInGroup());
                             }),
              cats_.end());
  free_cats_.erase(std::remove_if(free_cats_.begin(), free_cats_.end(),
                                  [](const std::shared_ptr<Cat>& cat) {
                                    return !(cat->GetIsInGroup());
                                  }),
                   free_cats_.end());
}

void Player::UpdateDogsAround(const std::list<std::shared_ptr<Dog>>& dogs)
    const {
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
  if (GetMainCat()->GetIsReachable()) {
    GetMainCat()->SetIsReachable(false);
    GetMainCat()->DecSpeed(constants::kCatRunCoefficient);
  }
  std::uniform_int_distribution<> x_destination
      (cat_group_.central_position_.GetX() - 1000,
       cat_group_.central_position_.GetX() + 1000);
  std::uniform_int_distribution<> y_destination
      (cat_group_.central_position_.GetY() - 1000,
       cat_group_.central_position_.GetY() + 1000);

  for (size_t i = 1; i < cats_.size(); i++) {
    cats_.at(i)->SetIsInGroup(false);
    cats_.at(i)->SetIsRunAway(true);
    cats_.at(i)->SetDestination(Point(x_destination(random_generator_),
                                      y_destination(random_generator_)));
    cats_.at(i)->SetCatState(CatState::kIsComingDestination);
  }
  cat_group_.DecGroup(cats_.size() - 1);
  cats_.erase(cats_.cbegin() + 1, cats_.cend());
  free_cats_.erase(std::remove_if(free_cats_.begin(), free_cats_.end(),
                                  [](const std::shared_ptr<Cat>& cat) {
                                    return !(cat->GetIsInGroup());
                                  }),
                   free_cats_.end());
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
                                       std::list<std::shared_ptr<PortalObject>>&
static_objects) {
  Point cat_position;
  Size distance;
  for (const auto& cat : cats_) {
    cat_position = cat->GetRigidPosition();
    for (auto& static_object : static_objects) {
      distance = cat_position.GetVectorTo(static_object->GetRigidPosition());
      if (distance.GetLength() < visibility_radius_) {
        static_object->SetIfMessageIsShown(true);
      } else {
        static_object->SetIfMessageIsShown(false);
      }
    }
  }
}

void Player::UpdateCatsGroup(const std::list<std::shared_ptr<Cat>>& all_cats) {
  for (auto& cat : cats_) {
    if (cat->GetCatState() == CatState::kReadyToBeDeleted) {
      SendCatToPortal(cat);
      continue;
    }
    for (auto& wild_cat : all_cats) {
      if (cat == wild_cat) {
        continue;
      }
      auto length = cat_group_.central_position_.
          GetVectorTo(wild_cat->GetRigidPosition()).GetLength();
      if (wild_cat->GetIsRunAway()) {
        continue;
      }
      if (length < cat_group_.first_radius_ &&
          !(wild_cat->GetIsInGroup())
          && wild_cat->GetCatState() != CatState::kIsGoingToSearch &&
          hunger_state_ != HungerState::kSevereHunger && !wild_cat->IsDead()) {
        cats_.push_back(wild_cat);
        free_cats_.push_back(wild_cat);
        wild_cat->SetIsInGroup(true);
        wild_cat->SetCatState(CatState::kIsFollowingPlayer);
        food_saturation_ += wild_cat->GetFoodSaturation();
        speed_of_hunger_ += constants::kSpeedOfHunger;
        max_food_saturation_ += constants::kMaxFoodSaturation;
        cat_group_.IncGroup();
      }
    }
  }
}

void Player::IsReachable(const std::list<std::shared_ptr<Dog>>& dogs) {
  for (auto& cat : cats_) {
    bool is_reachable{false};
    for (const auto& dog : dogs) {
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
  cat_group_.SetCentralPosition(GetMainCat()->GetRigidPosition());
  cat_group_.SetSpeed(GetMainCat()->GetSpeed());
  cat_group_.Tick(time);
  cat_group_.Move();
}

std::shared_ptr<Cat> Player::GetMainCat() {
  return cats_.at(0);
}

void Player::LosingCat(Point dog_position, const std::shared_ptr<Cat>& cat) {
  auto state = cat->GetCatState();
  if (state == CatState::kIsSearching || state == CatState::kIsGoingToSearch
      || state == CatState::kHasFinishedSearching) {
    return;
  }
  cat->SetIsInGroup(false);
  cat->SetIsRunAway(true);
  std::uniform_int_distribution<> x_destination(constants::kMinRunAwayDistance,
                                                constants::kMaxRunAwayDistance);
  cat->SetRunAwayDestination(dog_position, cat_group_.central_position_,
                             cat->GetRigidPosition(),
                             x_destination(random_generator_));
  cat->SetCatState(CatState::kIsComingDestination);

  max_food_saturation_ -= constants::kMaxFoodSaturation;
  double part_of_food_saturation = food_saturation_ / cats_.size();
  food_saturation_ -= part_of_food_saturation;
  cat->SetFoodSaturation(part_of_food_saturation);
  speed_of_hunger_ -= constants::kSpeedOfHunger;

  cat_group_.DecGroup();
  cats_.erase(std::remove_if(cats_.begin(), cats_.end(),
                             [](const std::shared_ptr<Cat>& cat) {
                               return !(cat->GetIsInGroup());
                             }),
              cats_.end());

  free_cats_.erase(std::remove_if(free_cats_.begin(), free_cats_.end(),
                                  [](const std::shared_ptr<Cat>& cat) {
                                    return !(cat->GetIsInGroup());
                                  }),
                   free_cats_.end());
}

std::shared_ptr<Cat> Player::SendCatToSearch(const Point& portal_coordinates,
                                             int search_time, const Rect&
portal_rect) {
  auto cat = free_cats_.begin();
  (*cat)->SetCatState(CatState::kIsGoingToSearch);
  (*cat)->SetSearchingTime(search_time);
  (*cat)->SetDestination(portal_coordinates);
  (*cat)->SetDestinationRect(portal_rect);
  free_cats_.erase(free_cats_.begin());
  return *cat;
}

bool Player::NotOnlyMainCat() {
  return (cats_.size() >= 2 && !free_cats_.empty());
}

void Player::FeedCats(double food) {
  food_saturation_ += food;
}

void Player::UpdateHunger() {
  food_saturation_ -= speed_of_hunger_;
  if (food_saturation_ < 0) {
    GetMainCat()->SetCatState(CatState::kIsDying);
  }
  if (food_saturation_ > max_food_saturation_) {
    food_saturation_ = max_food_saturation_;
  }
  if (food_saturation_ < max_food_saturation_ *
      constants::kSevereHungerPercent + constants::kEpsilon) {
    if (hunger_state_ == HungerState::kMediumHunger) {
      hunger_state_ = HungerState::kSevereHunger;
      DismissCats();
      cats_.at(0)->DecSpeed(constants::kChangeSpeedCoefficient);
      need_to_show_second_warning_ = true;
      food_saturation_ = constants::kMaxFoodSaturation * food_saturation_ /
          max_food_saturation_;
      max_food_saturation_ = constants::kMaxFoodSaturation;
      speed_of_hunger_ = constants::kSpeedOfHunger;
    }
    return;
  }
  if (food_saturation_ < max_food_saturation_ *
      constants::kMediumHungerPercent + constants::kEpsilon) {
    switch (hunger_state_) {
      case HungerState::kNotHungry: {
        hunger_state_ = HungerState::kMediumHunger;
        for (auto& cat : cats_) {
          cat->DecSpeed(constants::kChangeSpeedCoefficient);
        }
        need_to_show_first_warning_ = true;
        break;
      }
      case HungerState::kSevereHunger: {
        hunger_state_ = HungerState::kMediumHunger;
        cats_.at(0)->IncSpeed(constants::kChangeSpeedCoefficient);
        break;
      }
      default: {
        break;
      }
    }
    return;
  }
  if (hunger_state_ == HungerState::kSevereHunger) {
    hunger_state_ = HungerState::kNotHungry;
    cats_.at(0)->IncSpeed(constants::kChangeSpeedCoefficient *
    constants::kChangeSpeedCoefficient);
  }
  if (hunger_state_ == HungerState::kMediumHunger) {
    hunger_state_ = HungerState::kNotHungry;
    for (auto& cat : cats_) {
      cat->IncSpeed(constants::kChangeSpeedCoefficient);
    }
  }
}

bool Player::IfNeedToShowFirstWarning() const {
  return need_to_show_first_warning_;
}

void Player::ResetNeedToShowWarnings() {
  need_to_show_first_warning_ = false;
  need_to_show_second_warning_ = false;
}

bool Player::IfNeedToShowSecondWarning() const {
  return need_to_show_second_warning_;
}

double Player::GetFoodSaturation() const {
  return food_saturation_;
}

int Player::GetMaxFoodSaturation() const {
  return max_food_saturation_;
}

Point Player::GenerateRandomDestination() const {
  std::uniform_int_distribution<> x_destination
      (cat_group_.central_position_.GetX() - cat_group_.first_radius_,
       cat_group_.central_position_.GetX() + cat_group_.first_radius_);
  std::uniform_int_distribution<> y_destination
      (cat_group_.central_position_.GetY() - cat_group_.first_radius_ *
           constants::kSemiMinorCoefficient,
       cat_group_.central_position_.GetY() + cat_group_.first_radius_ *
           constants::kSemiMinorCoefficient);
  return Point(x_destination(random_generator_), y_destination
  (random_generator_));
}

void Player::DecHunger(double hunger) {
  food_saturation_ -= hunger;
}

void Player::SendCatToPortal(std::shared_ptr<Cat> cat) {
  cat->SetIsInGroup(false);
  cat->SetIsDead();
  cat_group_.DecGroup();
}
