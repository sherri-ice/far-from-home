#include "timer.h"

std::mt19937 Timer::random_generator_ = std::mt19937
    (std::chrono::system_clock::now().time_since_epoch().count());

Timer::Timer(int number_of_timers) {
  timers_.resize(number_of_timers);
  is_active_.resize(number_of_timers);
  for (int i = 0; i < number_of_timers; ++i) {
    timers_.at(i) = 0;
    is_active_.at(i) = false;
  }
}

void Timer::Tick(int delta_time) {
  for (int i = 0; i < timers_.size(); ++i) {
    if (is_active_.at(i)) {
      timers_.at(i) -= delta_time;
    }
  }
}

void Timer::StartTimerWithRandom(int min_time, int max_time, int
index_of_timer) {
  std::uniform_int_distribution<> random_time(min_time, max_time);
  timers_.at(index_of_timer) = random_time(random_generator_);
  is_active_.at(index_of_timer) = true;
}

bool Timer::IsTimeOut(int index_of_timer) {
  return timers_.at(index_of_timer) <= 0 && is_active_.at(index_of_timer);
}

void Timer::Stop(int index_of_timer) {
  timers_.at(index_of_timer) = 0;
  is_active_.at(index_of_timer) = false;
}

void Timer::Resize(int new_size) {
  timers_.resize(new_size, 0);
  is_active_.resize(new_size, false);
}

bool Timer::IsActive(int index_of_timer) {
  return is_active_.at(index_of_timer);
}

void Timer::Remove() {
  int size = timers_.size();
  for (int i = 0; i < size; i++) {
    if (timers_.at(i) <= 0 && is_active_.at(i)) {
      timers_.erase(timers_.cbegin() + i);
      is_active_.erase(is_active_.cbegin() + i);
      --i;
      --size;
    }
  }
}
int Timer::Time(int index) {
  return timers_.at(index);
}
