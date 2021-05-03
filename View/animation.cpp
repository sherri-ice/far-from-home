//
// Created by Yana on 15.04.21.
//

#include "animation.h"


std::mt19937 Animation::random_generator_ = std::mt19937
        (std::chrono::system_clock::now().time_since_epoch().count());


Animation::Animation(const std::vector<std::vector<QPixmap>> &frames, int animation_duration) : frames_(frames)
        , frames_rescaled_(frames) {
    time_between_frames_ = 0.1 * animation_duration / frames.size();
    Reset();
}

void Animation::Tick(int delta_time, const Size& velocity, bool is_moving, bool was_moving) {
    wait_till_next_frame_ -= delta_time;
    if (wait_till_next_frame_ >= 0) {
        return;
    }
    if (!is_moving) {
        if (was_moving) {
            SetCurrentRoad(4);
            current_frame_ = 0;
            wait_till_next_frame_ = time_between_frames_;
            return;
        }
        if (animation_loops_number == 0) {
            if (current_road_ == 6) {
                current_road_ = 7;
            } else {
                std::uniform_int_distribution<> random_time(4, 7);
                current_road_ = random_time(random_generator_);
            }
            if (current_road_ == 7) {
                animation_loops_number = 8;
            } else {
                animation_loops_number = 0;
            }
        } else {
            --animation_loops_number;
        }
    } else {
        double x = velocity.GetWidth();
        double y = velocity.GetHeight();
        if (std::abs(x) < 0.5) {
            if (y > 0.5) {
                SetCurrentRoad(0);
            } else {
                SetCurrentRoad(1);
            }
        } else if (x > 0.5) {
                SetCurrentRoad(3);
        } else {
                SetCurrentRoad(2);
        }
    }

  current_frame_ = (current_frame_ + 1) % 4;
  wait_till_next_frame_ = time_between_frames_;
}

void Animation::Reset() {
  wait_till_next_frame_ = time_between_frames_;
}

const QPixmap& Animation::GetCurrentFrame() const {
  return frames_rescaled_[current_road_][current_frame_];
}

[[maybe_unused]] const std::vector<QPixmap>& Animation::GetCurrentAnimationRoad() const {
  return frames_rescaled_[current_road_];
}

int Animation::GetCurrentAnimationDuration() const {
  return frames_.at(current_road_).size() * time_between_frames_;
}

void Animation::Rescale(Size to_size) {
  if (frames_.at(current_road_).empty()) {
    return;
  }
  if (std::abs(picture_size_.GetWidth() - to_size.GetWidth())
      + std::abs(picture_size_.GetHeight() - to_size.GetHeight()) < 5) {
    return;
  }
  for (uint32_t i = 0; i < frames_.at(current_road_).size(); i++) {
    frames_rescaled_[current_road_][i] =
        (frames_)[current_road_][i].scaled(to_size.GetWidth() + 1,
                                           to_size.GetHeight() + 1,
                                           Qt::KeepAspectRatio);
  }
  picture_size_ = to_size;
}

void Animation::SetCurrentRoad(int road) {
  current_road_ = road;
}


