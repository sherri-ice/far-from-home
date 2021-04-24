#include "player.h"

Player::Player(const std::shared_ptr<Cat>& cat) {
  cats_.push_back(cat);
}

std::vector<std::shared_ptr<Cat>> Player::GetCats() const {
  return cats_;
}

void Player::OrderCatsToMove(Size velocity) {
  cats_.at(0)->SetVelocityFromPlayer(velocity);
  Size cat_velocity;
  double vector_to_group;

  for (size_t i = 1; i < cats_.size(); i++) {
    vector_to_group = cats_.at(i)->GetDrawPosition().
        GetVectorTo(cats_.at(0)->GetDrawPosition()).GetLength();

    if (vector_to_group < first_group_radious_) {
      timer_to_go_home_.Stop(i);
      if (velocity == Size(0, 0)) {
        cat_velocity = velocity;
      } else if (!velocity.GetWidth()) {
        cat_velocity = Size(pow(-1, i) * 0.5, velocity.GetHeight() * 0.3 * i);
      } else if (!velocity.GetHeight()) {
        cat_velocity = Size(velocity.GetWidth() * 0.9 * i, pow(-1, i) * 0.4);
      } else {
        cat_velocity = Size(velocity.GetWidth() * 0.3 * pow(-1, i) +
            pow(-1, i) * 0.6, velocity.GetHeight() * 0.2 * i * pow(-1, i));
      }
    } else if (vector_to_group < second_group_radious_) {
      cat_velocity = cats_.at(i)->GetDrawPosition().GetVectorTo
          (cats_.at(i - 1)->GetDrawPosition() +
          Size(pow(-1, i) * cats_.at(i)->GetSize().GetHeight() / 2,
               pow(-1, i) * cats_.at(i)->GetSize().GetWidth() / 2));
    } else {
       cat_velocity = Size(0, 0);
       if (!timer_to_go_home_.IsActive(i)) {
        timer_to_go_home_.StartTimerWithRandom(constants::kMinTimeToGoHome,
                                               constants::kMaxTimeToGoHome, i);
      }
       if (timer_to_go_home_.IsTimeOut(i)) {
        cat_velocity = cats_.at(i)->GetDrawPosition().
            GetVectorTo(cats_.at(i)->GetHomePosition());
        cats_.at(i)->SetIsInGroup(false);
      }
    }

    cats_.at(i)->SetVelocity(cat_velocity);
  }

  timer_to_go_home_.Remove();
  cats_.erase(std::remove_if(cats_.begin(), cats_.end(),
      [](const std::shared_ptr<Cat>& cat){return !(cat->GetIsInGroup());}),
              cats_.end());
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
  for (size_t i = 1; i < cats_.size(); i++) {
    cats_.at(i)->SetIsInGroup(false);
    auto velocity = cats_.at(i)->GetDrawPosition().
        GetVectorTo(cats_.at(i)->GetHomePosition());
    cats_.at(i)->SetVelocity(velocity);
  }
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

void Player::Tick(int time) {
  view_circle_.Tick();
  timer_to_go_home_.Tick(time);
}

void Player::UpdateCatsGroup(const std::list<std::shared_ptr<Cat>>& cats) {
  for (auto& cat : cats_) {
    for (auto& wild_cat : cats) {
      if (cat == wild_cat) {
        continue;
      }
      auto length = cats_.at(0)->GetDrawPosition().
          GetVectorTo(wild_cat->GetDrawPosition()).GetLength();
      if (length < first_group_radious_ &&
          !(wild_cat->GetIsInGroup())) {
        cats_.push_back(wild_cat);
        wild_cat->SetIsInGroup(true);
      }
    }
  }
  timer_to_go_home_.Resize(cats_.size());
}