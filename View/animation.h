#ifndef VIEW_ANIMATION_H_
#define VIEW_ANIMATION_H_

#include <QPixmap>
#include <random>
#include <vector>

#include "../Model/constants.h"
#include "../Model/size.h"

enum AnimationState {
    kWalkDown = 0,
    kWalkUp = 1,
    kWalkLeft = 2,
    kWalkRight = 3,
    kHide = 5,
    kSendToPortal = 6,
    kBack = 5,
    kSit = 4,
    kSiting = 5,
    kIsDead = 7
};

class Animation {
 public:
  Animation() = default;
  explicit Animation(const std::vector<std::vector<QPixmap>>& frames);

  void Tick(int delta_time, const AnimationState& animation_state);
  void Reset();
  const QPixmap& GetCurrentFrame() const;
  void SetCurrentRoad(int road);

 private:

  uint current_road_ = 0;
  uint current_frame_ = 0;
  int wait_till_next_frame_ = 0;
  int time_between_frames_ = 100;

  static std::mt19937 random_generator_;

  std::vector<std::vector<QPixmap>> frames_{};
  std::vector<std::vector<QPixmap>> frames_rescaled_{};
};
#endif  // VIEW_ANIMATION_H_
