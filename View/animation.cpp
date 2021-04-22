//
// Created by Yana on 15.04.21.
//

#include "animation.h"

Animation::Animation(const std::vector<std::vector<QPixmap>> &frames, int animation_duration) : frames_(frames)
        , frames_rescaled_(frames)
{
    time_between_frames_ = 1.0 * animation_duration / frames.size();
    Reset();
}

void Animation::Tick(int delta_time, const Size& velocity, bool is_moving) {
    std::cout << "DELTA TIME" << delta_time << '\n';
    wait_till_next_frame_ -= delta_time;
    if (wait_till_next_frame_ >= 0) {
        return;
    }
    if (!is_moving) {
        if (current_road_ >= 4) {
            current_frame_ = 26;
        }
        std::cout << "TIME BW FRAMES: " << time_between_frames_ << '\n';
        std::srand(time(nullptr));
        if (current_frame_ == 26  && animation_loops_number == 0) {
                current_road_ = std::rand() % 4;

                if (current_road_ != 0) {
                    animation_loops_number = 1;
                } else {
                    animation_loops_number = std::rand() % 3 + 1;
                }
        } else {
            if (current_frame_ == 26) {
                --animation_loops_number;
            }
        }
    } else {
        int x = velocity.GetWidth();
        int y = velocity.GetHeight();
        if (x == 0) {
            if (y > 0) {
//                SetCurrentRoad(0); // down
                    SetCurrentRoad(5);
            } else {
//                SetCurrentRoad(1); // up
                SetCurrentRoad(5);
            }
        } else if (x > 0) {
                SetCurrentRoad(5);
        } else {
            SetCurrentRoad(4);
        }
        time_between_frames_ = 1;
    }

    current_frame_ = (current_frame_ + 1) % frames_.at(current_road_).size();
    wait_till_next_frame_ = time_between_frames_;
}

void Animation::Reset() {
    wait_till_next_frame_ = time_between_frames_;
}

const QPixmap &Animation::GetCurrentFrame() const {
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
                (frames_)[current_road_][i].scaled(to_size.GetWidth() + 1, to_size.GetHeight() + 1,
                                                   Qt::KeepAspectRatio);
    }
    picture_size_ = to_size;
}

void Animation::SetCurrentRoad(int road) {
    current_road_ = road;
}

Size Animation::GetPictureSize() const{
    return picture_size_;
}


