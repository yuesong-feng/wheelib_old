#pragma once
#include <string>
using std::string;

class Timer {
 private:
  string scope_;
  clock_t start_;
  clock_t last_;

 public:
  Timer() = delete;
  Timer(string &&str);
  ~Timer();
  void time();
};

Timer::Timer(string &&str) : scope_(std::move(str)), start_(0), last_(0) {}

void Timer::time() {
  clock_t now = clock();
  printf("time from last checkpoint: %lu ms\n", now - last_);
  last_ = now;
}

Timer::~Timer() {
  clock_t end = clock();
  printf("scope: %s, time: %lu ms\n", scope_.c_str(), end - start_);
}
