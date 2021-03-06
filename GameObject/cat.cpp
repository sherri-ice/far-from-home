#include "cat.h"

std::mt19937 Cat::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

Cat::Cat(const Size& size, double speed, const Point& position) :
    MovingObject(size, speed, position), home_position_(position),
    timers_(static_cast<int> (CatState::SIZE)) {
  destination_ = home_position_;
  timers_.StartTimerWithRandom(constants::kTimeToRestMin,
                               constants::kTimeToRestMax,
                               static_cast<int>(CatState::kIsResting));
}

void Cat::Draw(QPainter* painter, Resizer* resizer) const {
  if (is_visible_) {
    painter->save();
    auto position = resizer->GameToWindowCoordinate(position_);
    auto size = resizer->GameToWindowSize(size_);
    painter->translate(position.GetX(), position.GetY());
    auto draw_size = GetDrawSize(size);
    painter->drawPixmap(static_cast<int>(-draw_size.GetWidth() / 2),
                        static_cast<int>(-draw_size.GetHeight() / 2),
                        static_cast<int>(draw_size.GetWidth()),
                        static_cast<int>(draw_size.GetHeight()),
                        object_animation_.GetCurrentFrame());
    painter->restore();
  }
}

void Cat::Tick(int delta_time) {
  std::uniform_real_distribution<> pos_velocity(0, 1);
  std::uniform_real_distribution<> neg_velocity(-1, 0);
  std::uniform_real_distribution<> velocity(-1, 1);
  switch (cat_state_) {
    case CatState::kIsResting: {
      timers_.Stop(static_cast<int>(CatState::kIsFollowingPlayer));
      if (!timers_.IsActive(static_cast<int>(CatState::kIsResting))) {
        timers_.StartTimerWithRandom(constants::kTimeToRestMin,
                                     constants::kTimeToRestMax,
                                     static_cast<int>(CatState::kIsResting));
      }
      if (timers_.IsTimeOut(static_cast<int>(CatState::kIsResting))) {
        timers_.Stop(static_cast<int>(CatState::kIsResting));
        cat_state_ = CatState::kIsWalking;
        std::uniform_int_distribution<> times_to_change_directions
            (constants::kTimesToChangeDirectionMin,
             constants::kTimesToChangeDirectionsMax);
        change_directions_count_ = times_to_change_directions
            (random_generator_);
        velocity_ = Size(velocity(random_generator_), velocity
            (random_generator_));
        saved_walking_velocity_ = velocity_;
        --change_directions_count_;
        timers_.StartTimerWithRandom(constants::kTimeToWalkMin,
                                     constants::kTimeToWalkMax,
                                     static_cast<int>(CatState::kIsWalking));
      }
      break;
    }
    case CatState::kIsWalking: {
      if (timers_.IsTimeOut(static_cast<int>(CatState::kIsWalking))) {
        if (change_directions_count_ != 0) {
          velocity_ = Size(velocity(random_generator_), velocity
              (random_generator_));
          saved_walking_velocity_ = velocity_;
          --change_directions_count_;
          timers_.StartTimerWithRandom(constants::kTimeToWalkMin,
                                       constants::kTimeToWalkMax,
                                       static_cast<int>(CatState::kIsWalking));
        } else {
          timers_.Stop(static_cast<int>(CatState::kIsWalking));
          cat_state_ = CatState::kIsComingDestination;
          destination_ = home_position_;
        }
      }
      velocity_ = saved_walking_velocity_;
      if (velocity_.GetLength() > constants::kEpsilon) {
        velocity_ /= velocity_.GetLength();
        velocity_ *= delta_time * speed_ / constants::kTimeScale;
      }
      break;
    }
    case CatState::kIsComingDestination: {
      if (position_ == destination_) {
        if (is_reachable_cat_) {
          is_reachable_cat_ = false;
          DecSpeed(constants::kCatRunCoefficient);
        }
        is_run_away_ = false;
        cat_state_ = CatState::kIsResting;
        velocity_ = Size(0, 0);
        timers_.StartTimerWithRandom(constants::kTimeToRestMin,
                                     constants::kTimeToRestMax,
                                     static_cast<int>(CatState::kIsResting));
      } else {
        velocity_ = position_.GetVelocityVector(destination_, delta_time *
            speed_ / constants::kTimeScale);
      }
      break;
    }
    case CatState::kIsFollowingPlayer: {
      if (timers_.IsTimeOut(static_cast<int>(CatState::kIsFollowingPlayer)) ||
          !timers_.IsActive(static_cast<int>(CatState::kIsFollowingPlayer))) {
        if (velocity_ == Size(1, 1)) {
          velocity_ = Size(pos_velocity(random_generator_),
                           pos_velocity(random_generator_));
        } else if (velocity_ == Size(1, -1)) {
          velocity_ = Size(pos_velocity(random_generator_),
                           neg_velocity(random_generator_));
        } else if (velocity_ == Size(-1, 1)) {
          velocity_ = Size(neg_velocity(random_generator_),
                           pos_velocity(random_generator_));
        } else if (velocity_ == Size(-1, -1)) {
          velocity_ = Size(neg_velocity(random_generator_),
                           neg_velocity(random_generator_));
        } else if (velocity_ == Size(0, 1)) {
          velocity_ = Size(velocity(random_generator_),
                           pos_velocity(random_generator_));
        } else if (velocity_ == Size(1, 0)) {
          velocity_ = Size(pos_velocity(random_generator_),
                           velocity(random_generator_));
        } else if (velocity_ == Size(0, -1)) {
          velocity_ = Size(velocity(random_generator_),
                           neg_velocity(random_generator_));
        } else if (velocity_ == Size(-1, 0)) {
          velocity_ = Size(neg_velocity(random_generator_),
                           velocity(random_generator_));
        }
        timers_.StartTimerWithRandom(constants::kTimeToFollowMin,
                                     constants::kTimeToFollowMax,
                                     static_cast<int>
                                     (CatState::kIsFollowingPlayer));
      }
      if (velocity_.GetLength() > constants::kEpsilon) {
        velocity_ /= velocity_.GetLength();
        velocity_ *= delta_time * speed_ / constants::kTimeScale;
      }
      break;
    }
    case CatState::kIsMainCat: {
      if (velocity_.GetLength() > constants::kEpsilon) {
        velocity_ /= velocity_.GetLength();
        velocity_ *= delta_time * speed_ / constants::kTimeScale;
      }
      break;
    }
    case CatState::kIsGoingToSearch: {
      timers_.Stop(static_cast<int>(CatState::kIsFollowingPlayer));
      if (position_ == destination_) {
        cat_state_ = CatState::kIsSearching;
      }
      came_back_to_player = false;
      velocity_ = position_.GetVelocityVector(destination_, delta_time *
          speed_ / constants::kTimeScale);
      break;
    }
    case CatState::kIsSearching: {
      if (!timers_.IsActive(static_cast<int>(CatState::kIsSearching))) {
        timers_.Start(searching_time_,
                      static_cast<int>(CatState::kIsSearching));
        is_hidding_ = true;
      } else {
        is_hidding_ = false;
        is_visible_ = false;
      }
      if (timers_.IsTimeOut(static_cast<int>(CatState::kIsSearching))) {
        cat_state_ = CatState::kHasFinishedSearching;
        is_visible_ = true;
        is_back_ = true;
      }
      break;
    }
    case CatState::kHasFinishedSearching: {
      timers_.Stop(static_cast<int>(CatState::kIsSearching));
      is_back_ = false;
      if (position_ == destination_) {
        cat_state_ = CatState::kIsFollowingPlayer;
      }
      velocity_ = position_.GetVelocityVector(destination_, delta_time *
          speed_ / constants::kTimeScale);
      break;
    }
    case CatState::kNeedsToBeSendHome: {
      if (position_ == destination_) {
        timers_.Stop(static_cast<int>(CatState::kIsFollowingPlayer));
        if (!timers_.IsActive(static_cast<int>(CatState::kNeedsToBeSendHome))) {
          timers_.Start(time_for_cats_homesending_,
                        static_cast<int>(CatState::kNeedsToBeSendHome));
          is_ready_to_be_sent_home = true;
        }
      } else {
        velocity_ = position_.GetVelocityVector(destination_, delta_time *
            speed_ / constants::kTimeScale);
      }
      if (timers_.IsTimeOut(static_cast<int>(CatState::kNeedsToBeSendHome))) {
        cat_state_ = CatState::kReadyToBeDeleted;
      }
      break;
    }
    case CatState::kReadyToBeDeleted: {
      timers_.Stop(static_cast<int>(CatState::kNeedsToBeSendHome));
      break;
    }
    case CatState::kIsDying: {
      if (!timers_.IsActive(static_cast<int>(CatState::kIsDying))) {
        timers_.Start(death_time_,
                      static_cast<int>(CatState::kIsDying));
        is_ready_to_die = true;
    } else {
        velocity_ = Size(0, 0);
    }
      if (timers_.IsTimeOut(static_cast<int>(CatState::kIsDying))) {
        cat_state_ = CatState::kIsDead;
      }
      break;
    }
    case CatState::kIsDead: {
      timers_.Stop(static_cast<int>(CatState::kIsDying));
      is_main_cat_dead_ = true;
      break;
    }
    default: {
      break;
    }
  }
  timers_.Tick(delta_time);

  if (!GetIsInGroup()) {
    food_saturation_ -= speed_of_hunger_;
    if (food_saturation_ < 30) {
      FeedCat();
    }
  }
}

bool Cat::GetIsInGroup() const {
  return is_in_group_;
}

void Cat::SetIsInGroup(bool in_group) {
  is_in_group_ = in_group;
}

void Cat::SetCatState(CatState cat_state) {
  cat_state_ = cat_state;
}

CatState Cat::GetCatState() {
  return cat_state_;
}

void Cat::SetIsReachable(bool is_reachable) {
  is_reachable_cat_ = is_reachable;
}

Timer Cat::GetTimer() {
  return timers_;
}

bool Cat::GetIsReachable() {
  return is_reachable_cat_;
}

void Cat::SetHomePosition(const Point& position) {
  home_position_ = position;
}

int Cat::GetSearchingTime() const {
  return searching_time_;
}

void Cat::SetSearchingTime(int searching_time) {
  searching_time_ = searching_time;
}

bool Cat::GetIsVisible() {
  return is_visible_;
}

double Cat::GetFoodSaturation() const {
  return food_saturation_;
}

void Cat::FeedCat() {
  std::uniform_int_distribution<> food(20, 50);
  food_saturation_ += food(random_generator_);
}

void Cat::SetFoodSaturation(double food_saturation) {
  food_saturation_ = food_saturation;
}

bool Cat::IsComingDestination() const {
  return cat_state_ == CatState::kIsComingDestination;
}

bool Cat::IsMainCat() const {
  return cat_state_ == CatState::kIsMainCat;
}

void Cat::SetDestinationRect(const Rect& rect) {
  destination_rect_ = rect;
}

bool Cat::IsGoingToSearch() const {
  return cat_state_ == CatState::kIsGoingToSearch;
}

Rect Cat::GetDestinationRect() const {
  return destination_rect_;
}

void Cat::SetIsRunAway(bool is_run_away) {
  is_run_away_ = is_run_away;
}

bool Cat::GetIsRunAway() const {
  return is_run_away_;
}

bool Cat::HasFinishedSearch() const {
  return cat_state_ == CatState::kHasFinishedSearching;
}

void Cat::ComeHome() {
  timers_.Stop(static_cast<int>(CatState::kIsWalking));
  cat_state_ = CatState::kIsComingDestination;
  destination_ = home_position_;
}

bool Cat::IsDying() const {
  return cat_state_ == CatState::kIsDying;
}
