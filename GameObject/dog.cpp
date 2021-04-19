#include "dog.h"

std::mt19937 Dog::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

Dog::Dog(const Size& size,
         double speed,
         const Point& position, double visibility_radius) : MovingObject
         (size, speed, position), visibility_radius_
    (visibility_radius), home_position_(position) {
  destination_ = home_position_;
  StartTimerAndChangeDestination();
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
  if (dog_state_ == DogState::kChasingCat) {
    painter->setBrush(Qt::black);
  } else if (dog_state_ == DogState::kIsResting) {
    painter->setBrush(Qt::darkBlue);
  } else {
    painter->setBrush(Qt::blue);
  }
  painter->drawEllipse(-object_width / 2,
                       -object_height / 2,
                       object_width,
                       object_height);
  painter->restore();
}

void Dog::Tick(int delta_time) {
  if (dog_state_ == DogState::kIsComingHome && position_ == home_position_) {
    dog_state_ = DogState::kIsResting;
  }
  if (timer_to_walk_.remainingTime() <= constants::kTimeBetweenTicks &&
  timer_to_walk_.remainingTime() != -1) {
    timer_to_walk_.stop();
    TimeOut();
  } else if (timer_to_walk_.remainingTime() == -1) {
    StartTimerAndChangeDestination();
  }
  if (reachable_cat_) {
    destination_ = reachable_cat_->GetDrawPosition();
    dog_state_ = DogState::kChasingCat;
    velocity_ = position_.GetVectorTo(destination_);
  } else if (dog_state_ == DogState::kChasingCat) {
    destination_ = home_position_;
    dog_state_ = DogState::kIsComingHome;
    velocity_ = position_.GetVectorTo(destination_);
  } else if (dog_state_ == DogState::kIsComingHome) {
    velocity_ = position_.GetVectorTo(destination_);
  }
}

void Dog::Move(int delta_time) {
  if (dog_state_ == DogState::kIsWalking) {
    if (velocity_.GetLength() > constants::kEpsilon) {
      velocity_ /= velocity_.GetLength();
    }
    position_ += velocity_ * walking_speed_ * delta_time *
        constants::kTimeScale;
  } else {
    MoveToDestination(delta_time);
  }
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

void Dog::StartTimerAndChangeDestination() {
  std::uniform_int_distribution<> time_to_rest(5000, 7000);
  std::uniform_int_distribution<> velocity(-1, 1);
  std::uniform_int_distribution<> time_to_walk(1500, 3500);
  if (dog_state_ == DogState::kIsResting) {
    timer_to_walk_.start(time_to_rest(random_generator_));
  } else if (dog_state_ == DogState::kIsWalking && change_directions_count_
  != 0) {
    velocity_ = Size(velocity(random_generator_), velocity(random_generator_));
    --change_directions_count_;
    timer_to_walk_.start(time_to_walk(random_generator_));
  }
}

void Dog::TimeOut() {
  std::uniform_int_distribution<> times_to_change_directions(2, 5);
  if (dog_state_ == DogState::kIsResting) {
    dog_state_ = DogState::kIsWalking;
    change_directions_count_ = times_to_change_directions(random_generator_);
    StartTimerAndChangeDestination();
  } else if (dog_state_ == DogState::kIsWalking && change_directions_count_
  != 0) {
    StartTimerAndChangeDestination();
  } else if (dog_state_ == DogState::kIsWalking && change_directions_count_
  == 0) {
    dog_state_ = DogState::kIsComingHome;
    destination_ = home_position_;
  }
}

void Dog::MoveToDestination(int delta_time) {
  if (velocity_.GetLength() > constants::kEpsilon) {
    velocity_ /= velocity_.GetLength();
  }
  if (dog_state_ == DogState::kIsComingHome) {
    velocity_ *= delta_time * walking_speed_ * constants::kTimeScale;
  } else {
    velocity_ *= delta_time * speed_ * constants::kTimeScale;
  }
  Size first_vector = (position_ + velocity_).GetVectorTo(destination_);
  Size second_vector = position_.GetVectorTo(destination_);
  if (first_vector.GetWidth() * second_vector.GetWidth() <=
      constants::kEpsilon && first_vector.GetHeight() * second_vector
      .GetHeight() <= constants::kEpsilon) {
    position_ = destination_;
  } else {
    position_ += velocity_;
  }
}
