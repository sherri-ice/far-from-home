#include "animation.h"

Animation::Animation(const std::vector<std::vector<QPixmap>> &frames) :
    frames_(frames), frames_rescaled_(frames) {
    Reset();
}

void Animation::Tick(int delta_time, const AnimationState& animation_state) {
  wait_till_next_frame_ -= delta_time;
  if (wait_till_next_frame_ >= 0) {
    return;
  }
  SetCurrentRoad(animation_state);
  current_frame_ = (current_frame_ + 1) % 4;
  wait_till_next_frame_ = time_between_frames_;
}

void Animation::Reset() {
  wait_till_next_frame_ = time_between_frames_;
  current_frame_ = 0;
}

const QPixmap& Animation::GetCurrentFrame() const {
  return frames_rescaled_[current_road_][current_frame_];
}

const std::vector<QPixmap>& Animation::GetCurrentAnimationRoad() const {
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
