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

void Animation::SetCurrentRoad(int road) {
  current_road_ = road;
}
