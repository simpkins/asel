// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/inttypes.h"

namespace asel {

namespace detail {
constexpr intmax_t sign(intmax_t n) {
  return n >= 0 ? 1 : -1;
}
constexpr intmax_t abs(intmax_t n) {
  return n >= 0 ? n : -n;
}
constexpr intmax_t gcd(intmax_t a, intmax_t b) {
  if (a == 0) {
    return abs(b);
  }
  if (b == 0) {
    return abs(a);
  }
  return gcd(b, a % b);
}
} // namespace detail

template <intmax_t Num, intmax_t Denom = 1>
class ratio {
public:
  static constexpr intmax_t num =
      detail::sign(Denom) * Num / detail::gcd(Num, Denom);
  static constexpr intmax_t den = detail::abs(Denom) / detail::gcd(Num, Denom);
};

using milli = ratio<1, 1000>;
using micro = ratio<1, 1'000'000>;
using nano = ratio<1, 1'000'000'000>;

} // namespace asel
