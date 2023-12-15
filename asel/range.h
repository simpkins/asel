// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/array.h"
#include "asel/inttypes.h"
#include "asel/type_traits.h"

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

  // Automatic construction of a range from an array
  template <size_t N>
  explicit constexpr range(array<T, N> &data) noexcept
      : start_(data.data()), end_(data.data() + data.size()) {}
  template <typename U, size_t N>
  explicit constexpr range(
      const array<U, N> &data,
      std::enable_if_t<std::is_same_v<T, std::add_const_t<U>>, int> =
          0) noexcept
      : start_(data.data()), end_(data.data() + data.size()) {}

  constexpr T *data() const {
    return start_;
  }
  constexpr size_t size() const {
    return end_ - start_;
  }

  T &operator[](size_t index) const {
    return *(start_ + index);
  }

private:
  T *start_ = nullptr;
  T *end_ = nullptr;
};

#if ASEL_HAVE_STDLIB
using string_view = std::string_view;
#else
using string_view = ::asel::range<char const>;
#endif

} // namespace asel
