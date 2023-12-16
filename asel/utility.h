// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/type_traits.h"

namespace asel {

// forward
template <typename T>
[[nodiscard]] constexpr T &&forward(remove_reference_t<T> &value) noexcept {
  return static_cast<T &&>(value);
}

template <typename T>
[[nodiscard]] constexpr T &&forward(remove_reference_t<T> &&value) noexcept {
  static_assert(!is_lvalue_reference<T>::value,
                "must not use forward() to convert an rvalue to an lvalue");
  return static_cast<T &&>(value);
}

// move
template <typename T>
[[nodiscard]] constexpr remove_reference_t<T> &&move(T &&arg) noexcept {
  return static_cast<remove_reference_t<T> &&>(arg);
}

// integer_sequence, index_sequence
template <typename T, T... Ints>
class integer_sequence {
  typedef T value_type;
  static constexpr size_t size() noexcept {
    return sizeof...(Ints);
  }
};

// Clang has a compiler builtin for __make_integer_seq
#if __has_builtin(__make_integer_seq)
template <typename T, T Num>
using make_integer_sequence = __make_integer_seq<integer_sequence, T, Num>;
#else
// For GCC provides __integer_pack instead.
template <typename T, T Num>
using make_integer_sequence = integer_sequence<T, __integer_pack(Num)...>;
#endif

template <size_t... Ints>
using index_sequence = integer_sequence<size_t, Ints...>;

template <size_t Num>
using make_index_sequence = make_integer_sequence<size_t, Num>;

} // namespace asel
