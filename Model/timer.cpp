#include "timer.h"

Timer::Timer(int number_of_timers) : number_of_timers_(number_of_timers) {
  timers_.resize(number_of_timers);
  for (int i{0}; i < number_of_timers; ++i) {
    timers_.at(i).first = 0;
    timers_.at(i).second = false;
  }
}

void Timer::Tick(int delta_time) {
  for (int i{0}; i < number_of_timers_; ++i) {
    if (timers_.at(i).second) {
      timers_.at(i).first -= delta_time;
    }
  }
}

void Timer::Start(int time, int index_of_timer) {
  timers_.at(index_of_timer).first = time;
  timers_.at(index_of_timer).second = true;
}

bool Timer::IsTimeOut(int index_of_timer) {
  return timers_.at(index_of_timer).first <= 0;
}

void Timer::Stop(int index_of_timer) {
  timers_.at(index_of_timer).first = 0;
  timers_.at(index_of_timer).second = false;
}

bool Timer::IsNotActive(int index_of_timer) {
  return !timers_.at(index_of_timer).second;
}
