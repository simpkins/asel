// Copyright (c) 2023, Adam Simpkins
#pragma once

/*
 * Implementations of various parts of <type_traits>
 * For use when we are compiled without the standard library.
 */

namespace asel {

template <typename T, T Value>
struct integral_constant {
  static constexpr T value = Value;
  using value_type = T;
  using type = integral_constant<T, Value>;
  constexpr operator value_type() const noexcept {
    return value;
  }
  constexpr value_type operator()() const noexcept {
    return value;
  }
};
template <bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

template <typename T>
struct remove_reference {
  using type = T;
};
template <typename T>
struct remove_reference<T &> {
  using type = T;
};
template <typename T>
struct remove_reference<T &&> {
  using type = T;
};
template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
struct is_lvalue_reference : public false_type {};
template <typename T>
struct is_lvalue_reference<T &> : public true_type {};

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

// Clang and gcc provide builtins for is_same
template <typename T, typename U>
struct is_same : public bool_constant<__is_same_as(T, U)> {};
template <typename T, typename U>
inline constexpr bool is_same_v = __is_same_as(T, U);

} // namespace asel
