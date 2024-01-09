// Copyright (c) 2024, Adam Simpkins
#pragma once

#include <esp_timer.h>
#include <chrono>

namespace asel {

/**
 * An alternative to std::chrono::steady_clock that simply makes a call to
 * esp_timer_get_time().
 */
class esp_steady_clock {
public:
  static constexpr bool is_steady = true;
  using duration = std::chrono::microseconds;
  using rep = std::chrono::microseconds::rep;
  using period = std::chrono::microseconds::period;
  using time_point = std::chrono::time_point<esp_steady_clock>;

  static time_point now() {
    return time_point(duration(esp_timer_get_time()));
  }
};

} // namespace asel
