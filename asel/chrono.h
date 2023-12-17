// Copyright (c) 2023, Adam Simpkins
#pragma once

#if ASEL_HAVE_STDLIB
#include <chrono>

namespace asel::chrono {
using std::chrono::days;
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::hours;
using std::chrono::microseconds;
using std::chrono::milliseconds;
using std::chrono::minutes;
using std::chrono::nanoseconds;
using std::chrono::seconds;
using std::chrono::steady_clock;
using std::chrono::time_point;
} // namespace asel::chrono

namespace asel {
inline namespace literals {
inline namespace chrono_literals {
using namespace std::literals::chrono_literals;
}
} // namespace literals
} // namespace asel
#else
#include "asel/ratio.h"

namespace asel::chrono {

template <class Rep, class Period = ratio<1>>
class duration {
public:
  using rep = Rep;
  using period = Period;

  constexpr duration() noexcept = default;
  explicit constexpr duration(Rep v) : value_(v) {}

  rep count() const {
    return value_;
  }

private:
  Rep value_ = 0;
};

// Note: we don't meet the standard's requirements for the bitwidth
// of Rep for all of these values.  The standard basically requires that
// seconds, milliseconds, microseconds, and nanoseconds all use 64-bit
// integers.  For our use case on embedded platforms we are intentionally using
// smaller integers in some cases here.
using nanoseconds = duration<int32_t, nano>;
using microseconds = duration<int32_t, micro>;
using milliseconds = duration<int32_t, milli>;
using seconds = duration<int32_t>;
using minutes = duration<int32_t, ratio<60>>;
using hours = duration<int32_t, ratio<3600>>;
using days = duration<int32_t, ratio<86400>>;

template <class Clock, class Duration = typename Clock::duration>
class time_point {
private:
};

template <class ToDuration, class Rep, class Period>
constexpr ToDuration duration_cast(const duration<Rep, Period> &d);

template <class Rep, class Period = ratio<1>>
class SteadyClockT {
public:
  using rep = Rep;
  using period = Period;
  using duration = ::asel::chrono::duration<rep, period>;
  using time_point = ::asel::chrono::time_point<SteadyClockT<Rep, Period>>;
  static constexpr bool is_steady = true;

  static time_point now();
};

using steady_clock = SteadyClockT<int64_t, microseconds>;

} // namespace asel::chrono

namespace asel {
inline namespace literals {
inline namespace chrono_literals {

_Pragma("GCC diagnostic push")
    _Pragma("GCC diagnostic ignored \"-Wuser-defined-literals\"")

        constexpr asel::chrono::nanoseconds
        operator""ns(unsigned long long n) {
  return asel::chrono::nanoseconds(n);
}
constexpr asel::chrono::microseconds operator""us(unsigned long long n) {
  return asel::chrono::microseconds(n);
}
constexpr asel::chrono::milliseconds operator""ms(unsigned long long n) {
  return asel::chrono::milliseconds(n);
}
constexpr asel::chrono::seconds operator""s(unsigned long long n) {
  return asel::chrono::seconds(n);
}
constexpr asel::chrono::hours operator""h(unsigned long long n) {
  return asel::chrono::hours(n);
}
constexpr asel::chrono::days operator""d(unsigned long long n) {
  return asel::chrono::days(n);
}

_Pragma("GCC diagnostic pop")

} // namespace chrono_literals
} // namespace literals
} // namespace asel
#endif
