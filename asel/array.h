// Copyright (c) 2023, Adam Simpkins
#pragma once

#if ASEL_HAVE_STDLIB
#include <array>
namespace asel {
using std::array;
using std::to_array;
}
#else // !ASEL_HAVE_STDLIB

#include "asel/inttypes.h"
#include "asel/type_traits.h"
#include "asel/utility.h"

namespace asel {

namespace detail {
template <typename T, size_t N>
class array_traits {
public:
  using storage_type = T[N];

  static constexpr T const *data(const storage_type &s) {
    return s;
  }
  static constexpr T *data(storage_type &s) {
    return s;
  }
};

template <typename T>
class array_traits<T, 0> {
public:
  class storage_type;
  static constexpr T const *data(const storage_type &) {
    return nullptr;
  }
  static constexpr T *data(storage_type &) {
    return nullptr;
  }
};
} // namespace detail

template <typename T, size_t N>
struct array {
  constexpr T const *data() const {
    return detail::array_traits<T, N>::data(data_);
  }
  constexpr T *data() {
    return detail::array_traits<T, N>::data(data_);
  }
  constexpr size_t size() const {
    return N;
  }

  constexpr T const &operator[](size_t index) const {
    return *(data() + index);
  }
  constexpr T &operator[](size_t index) {
    return *(data() + index);
  }

  typename detail::array_traits<T, N>::storage_type data_;
};

namespace detail {
template <class T, size_t N, size_t... I>
constexpr array<remove_cv_t<T>, N> to_array_impl(T (&a)[N],
                                                 index_sequence<I...>) {
  return {{a[I]...}};
}
template <class T, size_t N, size_t... I>
constexpr array<remove_cv_t<T>, N> to_array_impl(T (&&a)[N],
                                                 index_sequence<I...>) {
  return {{move(a[I])...}};
}
} // namespace detail

template <class T, size_t N>
constexpr array<remove_cv_t<T>, N> to_array(T (&a)[N]) {
  return detail::to_array_impl(a, make_index_sequence<N>{});
}
template <class T, size_t N>
constexpr array<remove_cv_t<T>, N> to_array(T (&&a)[N]) {
  return detail::to_array_impl(move(a), make_index_sequence<N>{});
}

} // namespace asel

#endif // !ASEL_HAVE_STDLIB
