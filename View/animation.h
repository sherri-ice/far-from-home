//
// Created by Yana on 15.04.21.
//

#ifndef VIEW_ANIMATION_H
#define VIEW_ANIMATION_H

#include <iostream>
#include <vector>
#include <QPixmap>

#include "../Model/constants.h"
#include "../Model/size.h"


class Animation {
public:
    Animation() = default;
    explicit Animation(const std::vector<std::vector<QPixmap>>& frames,
    int animation_duration = constants::kTimeScale);

    void Tick(int delta_time, const Size& velocity, bool is_moving = false);
    void Reset();
    const QPixmap& GetCurrentFrame() const;
    const std::vector<QPixmap>& GetCurrentAnimationRoad() const;
    int GetCurrentAnimationDuration() const;
    void Rescale(Size to_size);
    void SetCurrentRoad(int road);
    Size GetPictureSize() const;

private:
    Size picture_size_{0, 0};

    //--------
    uint animation_loops_number = 2;
    uint current_road_ = 0;
    uint current_frame_ = 0;
    int wait_till_next_frame_ = 0;
    int time_between_frames_ = 0;

    std::vector<std::vector<QPixmap>> frames_;
    std::vector<std::vector<QPixmap>> frames_rescaled_;
};
#endif //VIEW_ANIMATION_H
