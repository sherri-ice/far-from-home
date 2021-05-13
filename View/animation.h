#ifndef VIEW_ANIMATION_H_
#define VIEW_ANIMATION_H_

#include <iostream>
#include <vector>
#include <QPixmap>
#include <random>

#include "../Model/constants.h"
#include "../Model/size.h"

enum AnimationState {
    kWalkDown = 0,
    kWalkUp = 1,
    kWalkLeft = 2,
    kWalkRight = 3,
    kSit = 4,
    kLicking = 5,
    kSleeping = 6,
    kSiting = 7
};

class Animation {
 public:
  Animation() = default;
  explicit Animation(const std::vector<std::vector<QPixmap>>& frames,
                     int animation_duration = 10);

  void Tick(int delta_time, const AnimationState& animation_state);
  void Reset();
  const QPixmap& GetCurrentFrame() const;
  const std::vector<QPixmap>& GetCurrentAnimationRoad() const;
  int GetCurrentAnimationDuration() const;
  void Rescale(Size to_size);
  void SetCurrentRoad(int road);

 private:
  Size picture_size_{0, 0};

    //--------
    uint animation_loops_number = 2;
    uint current_road_ = 0;
    uint current_frame_ = 0;
    int wait_till_next_frame_ = 0;
    int time_between_frames_ = 25;
    //---------

    static std::mt19937 random_generator_;


  std::vector<std::vector<QPixmap>> frames_{};
  std::vector<std::vector<QPixmap>> frames_rescaled_{};
};
#endif  // VIEW_ANIMATION_H_
