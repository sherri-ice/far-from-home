#include "dog.h"

std::mt19937 Dog::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

Dog::Dog(const Size& size,
         double speed,
         const Point& position,
         double visibility_radius,
         double walking_speed) : MovingObject(size, speed, position),
                                 home_position_(position), visibility_radius_
                                         (visibility_radius), walking_speed_
                                         (walking_speed), timers_(static_cast<int>
                                                                  (DogState::SIZE)) {
    destination_ = home_position_;
    timers_.StartTimerWithRandom(constants::kTimeToRestMin,
                                 constants::kTimeToRestMax);
}

void Dog::Draw(QPainter* painter, Resizer* resizer) const {
    rigid_body_.Draw(painter, resizer);
    painter->save();
    auto position = resizer->GameToWindowCoordinate(position_);
    auto size = resizer->GameToWindowSize(size_);
    painter->translate(position.GetX(), position.GetY());
    int object_width = static_cast<int>(size.GetWidth());
    int object_height = static_cast<int>(size.GetHeight());
    if (is_visible_to_player_) {
        Size radius = resizer->GameToWindowSize(Size(visibility_radius_,
                                                     visibility_radius_));
        painter->drawEllipse(static_cast<int>(-radius.GetWidth()),
                             static_cast<int>(-radius.GetHeight() *
                                              constants::kSemiMinorCoefficient),
                             2 * static_cast<int>(radius.GetWidth()),
                             2 * static_cast<int>(radius.GetHeight() *
                                                  constants::kSemiMinorCoefficient));
    }
    painter->drawPixmap(-object_width / 2,
                         -object_height / 2,
                         object_width,
                         object_height, object_animation_->GetCurrentFrame());
    painter->restore();
}

void Dog::Tick(int delta_time) {
    timers_.Tick(delta_time);
    if (reachable_cat_) {
        timers_.Stop(static_cast<int>(DogState::kIsResting));
        timers_.Stop(static_cast<int>(DogState::kIsWalking));
        destination_ = reachable_cat_->GetRigidPosition();
        dog_state_ = DogState::kChasingCat;
        velocity_ = GetRigidPosition().GetVelocityVector(destination_, delta_time
                                                                       * speed_ / constants::kTimeScale);

        std::cout << velocity_.GetWidth() << " " << velocity_.GetHeight() << '\n';
    }

    std::uniform_int_distribution<> velocity(-1, 1);
  switch (dog_state_) {
    case DogState::kIsResting: {
      if (timers_.IsTimeOut(static_cast<int>(DogState::kIsResting))) {
        timers_.Stop(static_cast<int>(DogState::kIsResting));
        dog_state_ = DogState::kIsWalking;
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
          timers_.StartTimerWithRandom(constants::kTimeToWalkMin,
                                       constants::kTimeToWalkMax,
                                       static_cast<int>(DogState::kIsWalking));
        } else {
          timers_.Stop(static_cast<int>(DogState::kIsWalking));
          dog_state_ = DogState::kIsComingHome;
          destination_ = home_position_;
        }
      }
      if (velocity_.GetLength() > constants::kEpsilon) {
        velocity_ /= velocity_.GetLength();
        velocity_ *= delta_time * walking_speed_ / constants::kTimeScale;
      }
      break;
    }
    case DogState::kChasingCat: {
      if (!reachable_cat_) {
        destination_ = home_position_;
        dog_state_ = DogState::kIsComingHome;
        velocity_ = position_.GetVelocityVector(destination_, delta_time * walking_speed_ / constants::kTimeScale);
      }
      break;
    }
    case DogState::kIsComingHome: {
      if (position_ == home_position_) {
        dog_state_ = DogState::kIsResting;
        velocity_ = Size(0, 0);
        timers_.StartTimerWithRandom(constants::kTimeToRestMin,
                                     constants::kTimeToRestMax,
                                     static_cast<int>(DogState::kIsResting));
      } else {
        velocity_ = position_.GetVelocityVector(destination_, delta_time *
            walking_speed_ / constants::kTimeScale);
      }
      break;
    }
    default: {
      break;
    }
  }
    dog_state_ == DogState::kIsResting ? is_moving_ = false : is_moving_ = true;

    object_animation_->Tick(delta_time, velocity_, is_moving_, was_moving_);
     was_moving_ = is_moving_;
}

void Dog::SetIfItVisibleToPlayer(bool is_visible) {
  is_visible_to_player_ = is_visible;
}

void Dog::SetReachableCat(const std::vector<std::shared_ptr<Cat>>& cats) {
  reachable_cat_ = nullptr;
  Size min_distance = Size(visibility_radius_, visibility_radius_);
  for (const auto& cat : cats) {
    Size cat_distance = position_.GetVectorTo(cat->GetRigidPosition());
    if (CheckIfCanSeeCat(&(*cat)) &&
        cat_distance.GetLength() < min_distance.GetLength()) {
      reachable_cat_ = &(*cat);
      min_distance = cat_distance;
    }
  }
}

bool Dog::CheckIfCanSeeCat(const Cat* cat) const {
  return cat->GetRigidPosition().IsInEllipse(position_,
                                             visibility_radius_);
}

double Dog::GetVisibilityRadius() const {
  return visibility_radius_;
}
