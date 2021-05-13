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

void MovingObject::DecSpeed(double speed) {
  speed_ /= speed;
}

double MovingObject::GetSpeed() {
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


AnimationState MovingObject::GetAnimation() const {
    AnimationState animation_state;
    if (!is_moving_) {
        if (was_moving_) {
            return kSit;
        }
        // ну анимашка эта дерганая нормально так надоела пусть пока без рандома
        // std::uniform_int_distribution<> random_time(4, 7);
        // animation_state = static_cast<AnimationState>
        //                   (random_time(random_generator_));
        animation_state = kSiting;
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
