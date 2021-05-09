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

double MovingObject::GetSpeed() const {
    return speed_;
}

void MovingObject::Move(int delta_time) {
  position_ += velocity_;
}

AnimationState MovingObject::GetAnimation() const {
    AnimationState animation_state;
    if (!is_moving_) {
        if (was_moving_) {
            return kSit;
        }
        std::uniform_int_distribution<> random_time(4, 7);
        animation_state = static_cast<AnimationState>(random_time(random_generator_));
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