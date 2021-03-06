#include "dog.h"

std::mt19937 Dog::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

Dog::Dog(const Size& size,
         double speed,
         const Point& position,
         double visibility_radius,
         double walking_speed) : MovingObject(size, speed, position),
                                 home_position_(position), visibility_radius_
                                     (visibility_radius),
                                 walking_speed_
                                     (walking_speed),
                                 timers_(static_cast<int>
                                         (DogState::SIZE)) {
  destination_ = home_position_;
  std::uniform_int_distribution<>num_of_cats_to_run_away
                                  (dog_constants::kMinNumOfCatsToRunAway,
                                   dog_constants::kMaxNumOfCatsToRunAway);
  num_of_cats_to_run_away_ = num_of_cats_to_run_away(random_generator_);
  timers_.StartTimerWithRandom(dog_constants::kTimeToRestMin,
                               dog_constants::kTimeToRestMax);
}

void Dog::Draw(QPainter* painter, Resizer* resizer) const {
  painter->save();
  auto position = resizer->GameToWindowCoordinate(position_);
  auto size = resizer->GameToWindowSize(size_);
  painter->translate(position.GetX(), position.GetY());
  painter->restore();
  painter->save();
  painter->translate(position.GetX(), position.GetY());
  auto draw_size = GetDrawSize(size);

  painter->drawPixmap(static_cast<int>(-draw_size.GetWidth() / 2),
                      static_cast<int>(-draw_size.GetHeight() / 2),
                      static_cast<int>(draw_size.GetWidth()),
                      static_cast<int>(draw_size.GetHeight()),
                      object_animation_.GetCurrentFrame());
  painter->restore();
}

void Dog::Tick(int delta_time) {
  dog_state_ == DogState::kIsResting ? is_moving_ = false : is_moving_ = true;
  timers_.Tick(delta_time);

  if (reachable_cat_) {
    timers_.Stop(static_cast<int>(DogState::kIsResting));
    timers_.Stop(static_cast<int>(DogState::kIsWalking));
    destination_ = reachable_cat_->GetRigidPosition();
    dog_state_ = DogState::kChasingCat;
    velocity_ = GetRigidPosition().GetVelocityVector(destination_, delta_time
        * speed_ / constants::kTimeScale);
    is_run_away_ = false;
  }

  if (is_main_cat_caught_ && (dog_state_ != DogState::kIsComingHome)) {
    dog_state_ = DogState::kIsComingHome;
    destination_ = home_position_;
    timers_.StartTimerWithRandom(dog_constants::kTimeToComeHomeMin,
                                 dog_constants::kTimeToComeHomeMax,
                                 static_cast<int>(DogState::kIsComingHome));
  }

  std::uniform_int_distribution<> velocity(-1, 1);
  switch (dog_state_) {
    case DogState::kIsResting: {
      if (timers_.IsTimeOut(static_cast<int>(DogState::kIsResting))) {
        timers_.Stop(static_cast<int>(DogState::kIsResting));
        dog_state_ = DogState::kIsWalking;
        std::uniform_int_distribution<> times_to_change_directions
            (dog_constants::kTimesToChangeDirectionMin,
             dog_constants::kTimesToChangeDirectionsMax);
        change_directions_count_ = times_to_change_directions
            (random_generator_);
        velocity_ = Size(velocity(random_generator_), velocity
        (random_generator_));
        saved_walking_velocity_ = velocity_;
        --change_directions_count_;
        timers_.StartTimerWithRandom(dog_constants::kTimeToWalkMin,
                                     dog_constants::kTimeToWalkMax,
                                     static_cast<int>(DogState::kIsWalking));
      }
      break;
    }
    case DogState::kIsWalking: {
      if (timers_.IsTimeOut(static_cast<int>(DogState::kIsWalking))) {
        if (change_directions_count_ != 0) {
          velocity_ = Size(velocity(random_generator_), velocity
              (random_generator_));
          --change_directions_count_;
          saved_walking_velocity_ = velocity_;
          timers_.StartTimerWithRandom(dog_constants::kTimeToWalkMin,
                                       dog_constants::kTimeToWalkMax,
                                       static_cast<int>(DogState::kIsWalking));
        } else {
          timers_.Stop(static_cast<int>(DogState::kIsWalking));
          dog_state_ = DogState::kIsComingHome;
          destination_ = home_position_;
        }
      }
      velocity_ = saved_walking_velocity_;
      if (velocity_.GetLength() > constants::kEpsilon) {
        velocity_ /= velocity_.GetLength();
        velocity_ *= walking_speed_ * delta_time / constants::kTimeScale;
      }
      break;
    }
    case DogState::kChasingCat: {
      if (!reachable_cat_) {
        destination_ = home_position_;
        dog_state_ = DogState::kIsComingHome;
        velocity_ = position_.GetVelocityVector(destination_, delta_time *
            walking_speed_ / constants::kTimeScale);
      }
      break;
    }
    case DogState::kIsComingHome: {
      if (timers_.IsTimeOut(static_cast<int>(DogState::kIsComingHome))) {
        timers_.Stop(static_cast<int>(DogState::kIsComingHome));
        is_main_cat_caught_ = false;
      }
      if (position_ == home_position_) {
        is_run_away_ = false;
        dog_state_ = DogState::kIsResting;
        velocity_ = Size(0, 0);
        timers_.Stop(static_cast<int>(DogState::kIsComingHome));
        is_main_cat_caught_ = false;
        timers_.StartTimerWithRandom(dog_constants::kTimeToRestMin,
                                     dog_constants::kTimeToRestMax,
                                     static_cast<int>(DogState::kIsResting));
      } else {
        velocity_ = position_.GetVelocityVector(destination_, delta_time *
            walking_speed_ / constants::kTimeScale);
        if (is_run_away_) {
          velocity_ = position_.GetVelocityVector(destination_, delta_time *
              speed_ / constants::kTimeScale);
        } else {
          velocity_ = position_.GetVelocityVector(destination_, delta_time *
              walking_speed_ / constants::kTimeScale);
        }
      }
      break;
    }
    default: {
      break;
    }
  }
}

void Dog::SetIfItVisibleToPlayer(bool is_visible) {
  is_visible_to_player_ = is_visible;
}

void Dog::SetReachableCat(const std::vector<std::shared_ptr<Cat>>& cats) {
  reachable_cat_ = nullptr;
  Size min_distance = Size(visibility_radius_, visibility_radius_);
  for (const auto& cat : cats) {
    Size cat_distance = GetRigidPosition().GetVectorTo(cat->GetRigidPosition());
    if (!cat->IsDying() && CheckIfCanSeeCat(&(*cat)) &&
        cat_distance.GetLength() < min_distance.GetLength() &&
        !timers_.IsActive(static_cast<int>(DogState::kIsComingHome))
        && cat->GetCatState() != CatState::kIsSearching) {
      reachable_cat_ = &(*cat);
      min_distance = cat_distance;
    }
  }
}

bool Dog::CheckIfCanSeeCat(const Cat* cat) const {
  return cat->GetRigidPosition().IsInEllipse(GetRigidPosition(),
                                             visibility_radius_);
}

const Cat* Dog::GetReachableCat() {
  return reachable_cat_;
}

double Dog::GetVisibilityRadius() const {
  return visibility_radius_;
}

double Dog::GetWalkingSpeed() const {
  return walking_speed_;
}

void Dog::SetIsMainCatCaught(bool is_caught) {
  is_main_cat_caught_ = is_caught;
}

int Dog::GetNumOfCatsToRunAway() const {
  return num_of_cats_to_run_away_;
}

void Dog::RunAway(const Point& cat_position) {
  if (!is_run_away_) {
    std::uniform_int_distribution<>
        x_destination(constants::kMinRunAwayDistance,
                      constants::kMaxRunAwayDistance);
    SetRunAwayDestination(GetRigidPosition(), cat_position, GetRigidPosition(),
                          x_destination(random_generator_));
    home_position_ = destination_;
    dog_state_ = DogState::kIsComingHome;
    is_run_away_ = true;
  }
  reachable_cat_ = nullptr;
}

DogState Dog::GetDogState() {
  return dog_state_;
}

bool Dog::IsComingHome() const {
  return dog_state_ == DogState::kIsComingHome;
}

void Dog::ComeHome() {
  SetDestination(home_position_);
  dog_state_ = DogState::kIsComingHome;
}

bool Dog::IsMainCatCaught() const {
  return is_main_cat_caught_;
}
