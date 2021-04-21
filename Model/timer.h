#ifndef MODEL_TIMER_H_
#define MODEL_TIMER_H_

#include <vector>

class Timer {
 public:
  explicit Timer(int number_of_timers = 1);
  ~Timer() = default;

  void Tick(int delta_time);
  void Start(int time, int index_of_timer = 0);
  void Stop(int index_of_timer = 0);

  bool IsTimeOut(int index_of_timer = 0);
  bool IsNotActive(int index_of_timer = 0);


 private:
  std::vector<std::pair<int, bool>> timers_;
  int number_of_timers_;
};

#endif  // MODEL_TIMER_H_
