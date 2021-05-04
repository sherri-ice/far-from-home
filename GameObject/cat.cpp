#include <iostream>
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
  rigid_body_.Draw(painter, resizer);
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
  switch (cat_state_) {
    case CatState::kIsResting: {
     painter->setBrush(Qt::red);
      break;
    }
    case CatState::kIsWalking: {
      painter->setBrush(Qt::lightGray);
      break;
    }
    case CatState::kIsComingDestination: {
      painter->setBrush(Qt::darkMagenta);
      break;
    }
    case CatState::kIsDoingSomething: {
      painter->setBrush(Qt::yellow);
      break;
    }
    default: {
      painter->setBrush(Qt::darkRed);
      break;
    }
  }
  painter->drawEllipse(position.GetX() - size.GetWidth()/2,
                       position.GetY() - size.GetHeight()/2,
                       size.GetWidth(),
                       size.GetHeight());
  painter->restore();
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
      if (velocity_.GetLength() > constants::kEpsilon) {
        velocity_ /= velocity_.GetLength();
        velocity_ *= delta_time * speed_ / constants::kTimeScale;
      }
      break;
    }
    case CatState::kIsComingDestination: {
      if (position_ == destination_) {
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
      } else {
        if (!timers_.IsActive(static_cast<int>(CatState::kIsMainCat))) {
          timers_.StartTimerWithRandom(constants::kTimeToDoingSmthMin,
                                       constants::kTimeToDoingSmthMax,
                                       static_cast<int>(CatState::kIsMainCat));
        }
        if (timers_.IsTimeOut(static_cast<int>(CatState::kIsMainCat))) {
          timers_.Stop(static_cast<int>(CatState::kIsMainCat));
          cat_state_ = CatState::kIsDoingSomething;
          timers_.StartTimerWithRandom(constants::kTimeToDoingSmthMin,
                                       constants::kTimeToDoingSmthMax,
                                       static_cast<int>
                                       (CatState::kIsDoingSomething));
        }
      }
      break;
    }
    case CatState::kIsDoingSomething: {
      if (timers_.IsTimeOut(static_cast<int>(CatState::kIsDoingSomething)) ||
          velocity_ != Size(0, 0))    {
        cat_state_ = CatState::kIsMainCat;
        timers_.Stop(static_cast<int>(CatState::kIsDoingSomething));
      }
      break;
    }
    default: {
      break;
    }
  }
  timers_.Tick(delta_time);
}

bool Cat::GetIsInGroup() const {
  return is_in_group_;
}

void Cat::SetVelocityFromPlayer(Size velocity) {
  velocity_ = velocity;
}

void Cat::SetIsInGroup(bool in_group) {
  is_in_group_ = in_group;
}

Point Cat::GetHomePosition() const {
  return home_position_;
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
