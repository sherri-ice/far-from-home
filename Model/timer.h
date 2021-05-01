#ifndef MODEL_TIMER_H_
#define MODEL_TIMER_H_

#include <chrono>
#include <random>
#include <vector>

class Timer {
 public:
  explicit Timer(int number_of_timers = 1);
  ~Timer() = default;

  void Tick(int delta_time);
  void StartTimerWithRandom(int min_time, int max_time, int index_of_timer = 0);
  void Stop(int index_of_timer = 0);

  bool IsTimeOut(int index_of_timer = 0);

 private:
  std::vector<int> timers_;
  std::vector<bool> is_active_;
  static std::mt19937 random_generator_;
};

#endif  // MODEL_TIMER_H_
