#include "moving_object.h"

std::mt19937 MovingObject::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

MovingObject::MovingObject(
    const Size& size, double speed, const Point& position)
    : GameObject(size, position), speed_(speed) {
}

void MovingObject::SetSpeed(double speed) {
  speed_ = speed;
}

void MovingObject::IncSpeed(double speed) {
  speed_ *= speed;
}

void MovingObject::SetDestination(const Point& destination) {
  destination_ = destination;
}

void MovingObject::SetVelocity(Size velocity) {
  velocity_ = velocity;
}

void MovingObject::Move(int delta_time) {
  position_ += velocity_;
}

Size MovingObject::GetVelocity() const {
  return velocity_;
}

void MovingObject::DecSpeed(double speed) {
  speed_ /= speed;
}

double MovingObject::GetSpeed() const {
  return speed_;
}

void MovingObject::SetRunAwayDestination(const Point& first_pos,
                                         const Point& second_pos,
                                         const Point& pos, int x) {
  double y = (first_pos.GetX() - second_pos.GetX()) /
      (second_pos.GetY() - first_pos.GetY()) * x
      + pos.GetY() + (-first_pos.GetX() + second_pos.GetX()) /
      (second_pos.GetY() - first_pos.GetY()) * pos.GetX();
  destination_ = Point(x, y);
}

bool MovingObject::IsVelocityChange(Size main_velocity) {
  if (main_velocity.GetWidth() * velocity_.GetWidth() < 0 ||
      main_velocity.GetHeight() * velocity_.GetHeight() < 0) {
    return true;
  }
  return false;
}

AnimationState MovingObject::GetAnimationState() const {
  AnimationState animation_state;
  if (is_ready_to_die) {
    return  kIsDead;
  }

  if (is_ready_to_be_sent_home) {
    return kSendToPortal;
  }
  if (is_hidding_) {
    return kHide;
  }
  if (!is_visible_) {
    return kHide;
  }
  if (is_back_) {
    return kBack;
  }
  if (!is_moving_) {
    if (was_moving_) {
      return kSit;
    } else {
      return kSiting;
    }
  } else {
    double x = velocity_.GetWidth();
    double y = velocity_.GetHeight();
    if (std::abs(x) < 0.05) {
      if (y > 0.05) {
        animation_state = kWalkDown;
      } else {
        animation_state = kWalkUp;
      }
    } else if (x > 0.05) {
      animation_state = kWalkRight;
    } else {
      animation_state = kWalkLeft;
    }
  }
  return animation_state;
}

void MovingObject::SetAnimations(std::vector<std::vector<QPixmap>> animation) {
  object_animation_ = Animation(animation);
}

Size MovingObject::GetDrawSize(const Size& object_size) const {
  double object_width = object_size.GetWidth();
  double object_height = object_size.GetHeight();
  if (object_animation_.GetCurrentFrame().width() >= object_animation_
      .GetCurrentFrame().height()) {
    double scale_coeff = static_cast<double>(object_animation_.GetCurrentFrame()
        .height()) / object_animation_.GetCurrentFrame().width();
    object_height *= scale_coeff;
  } else {
    double scale_coeff = static_cast<double>(object_animation_.GetCurrentFrame()
        .width()) / object_animation_.GetCurrentFrame().height();
    object_width *= scale_coeff;
  }
  return Size(object_width, object_height);
}

void MovingObject::TickAnimation(int delta_time) {
  if (velocity_ != Size(0, 0)) {
    is_moving_ = true;
  } else {
    is_moving_ = false;
  }
  object_animation_.Tick(delta_time, GetAnimationState());
  was_moving_ = is_moving_;
}

Point MovingObject::GetDestination() const {
  return destination_;
}
bool MovingObject::IsMainCatDead() const {
  return is_main_cat_dead_;
}
