// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/inttypes.h"

#if ASEL_HAVE_STDLIB
#include <string_view>
#endif

namespace asel {

template <typename T>
class range {
public:
  constexpr range() noexcept = default;
  constexpr range(T *start, size_t size) noexcept
      : start_(start), end_(start + size) {}

  constexpr T *data() const {
    return start_;
  }
  constexpr size_t size() const {
    return end_ - start_;
  }

private:
  T *start_ = nullptr;
  T *end_ = nullptr;
};

#if ASEL_HAVE_STDLIB
using string_view = std::string_view;
#else
using string_view = ::asel::range<char>;
#endif

} // namespace asel
