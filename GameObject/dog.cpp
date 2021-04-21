#include "dog.h"

std::mt19937 Dog::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

Dog::Dog(const Size& size,
         double speed,
         const Point& position,
         double visibility_radius,
         double walking_speed) : MovingObject(size, speed, position),
         home_position_(position), visibility_radius_(visibility_radius),
         walking_speed_(walking_speed), timer_to_walk_() {
  destination_ = home_position_;
  StartTimer();
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
  switch (dog_state_) {
    case DogState::kChasingCat: {
      painter->setBrush(Qt::black);
      break;
    }
    case DogState::kIsResting: {
      painter->setBrush(Qt::darkBlue);
      break;
    }
    default: {
      painter->setBrush(Qt::blue);
    }
  }
  painter->drawEllipse(-object_width / 2,
                       -object_height / 2,
                       object_width,
                       object_height);
  painter->restore();
}

void Dog::Tick(int delta_time) {
  timer_to_walk_.Tick(delta_time);

  if (dog_state_ == DogState::kIsComingHome && position_ == home_position_) {
    dog_state_ = DogState::kIsResting;
  }

  if (timer_to_walk_.IsNotActive()) {
    StartTimer();
    ChangeVelocity();
  }
  if (timer_to_walk_.IsTimeOut()) {
    timer_to_walk_.Stop();
    TimeOut();
  }

  if (reachable_cat_) {
    destination_ = reachable_cat_->GetDrawPosition();
    dog_state_ = DogState::kChasingCat;
    position_.VelocityVector(destination_, velocity_, delta_time * speed_ /
    constants::kTimeScale);
  }

  switch (dog_state_) {
    case DogState::kChasingCat: {
      timer_to_walk_.Stop();
      if (!reachable_cat_) {
        destination_ = home_position_;
        dog_state_ = DogState::kIsComingHome;
        position_.VelocityVector(destination_, velocity_, delta_time *
        walking_speed_ / constants::kTimeScale);
      }
      break;
    }
    case DogState::kIsComingHome: {
      position_.VelocityVector(destination_, velocity_, delta_time *
      walking_speed_ / constants::kTimeScale);
      break;
    }
    case DogState::kIsWalking: {
      if (velocity_.GetLength() > constants::kEpsilon) {
        velocity_ /= velocity_.GetLength();
        velocity_ *= delta_time * walking_speed_ / constants::kTimeScale;
      }
      break;
    }
    default: {
      break;
    }
  }
}

void Dog::Move(int delta_time) {
  position_ += velocity_;
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

void Dog::StartTimer() {
  std::uniform_int_distribution<> time_to_rest(constants::kTimeToRestMin,
                                               constants::kTimeToRestMax);
  std::uniform_int_distribution<> time_to_walk(constants::kTimeToWalkMin,
                                               constants::kTimeToWalkMax);
  if (dog_state_ == DogState::kIsResting) {
    timer_to_walk_.Start(time_to_rest(random_generator_));
  } else if (dog_state_ == DogState::kIsWalking && change_directions_count_
  != 0) {
    timer_to_walk_.Start(time_to_walk(random_generator_));
  }
}

void Dog::ChangeVelocity() {
  std::uniform_int_distribution<> velocity(-1, 1);
  if (dog_state_ == DogState::kIsWalking && change_directions_count_ != 0) {
    velocity_ = Size(velocity(random_generator_), velocity(random_generator_));
    --change_directions_count_;
  }
}

void Dog::TimeOut() {
  std::uniform_int_distribution<> times_to_change_directions
  (constants::kTimesToChangeDirectionMin, constants::kTimesToChangeDirectionsMax);
  if (dog_state_ == DogState::kIsResting) {
    dog_state_ = DogState::kIsWalking;
    change_directions_count_ = times_to_change_directions(random_generator_);
    StartTimer();
    ChangeVelocity();
  } else if (dog_state_ == DogState::kIsWalking && change_directions_count_
  != 0) {
    StartTimer();
    ChangeVelocity();
  } else if (dog_state_ == DogState::kIsWalking && change_directions_count_
  == 0) {
    dog_state_ = DogState::kIsComingHome;
    destination_ = home_position_;
  }
}
