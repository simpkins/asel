// Copyright (c) 2023, Adam Simpkins
#pragma once

/*
 * Implementations of various parts of <type_traits>
 * For use when we are compiled without the standard library.
 */

namespace asel {

// integral_constant, bool_constant
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

// remove_reference
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

// remove_cv
template <typename T>
struct remove_cv {
  using type = T;
};
template <typename T>
struct remove_cv<T const> {
  using type = T;
};
template <typename T>
struct remove_cv<T volatile> {
  using type = T;
};
template <typename T>
struct remove_cv<T const volatile> {
  using type = T;
};
template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

// add_const
template <typename T>
struct add_const {
  using type = T const;
};
template <typename T>
struct add_const<T const> {
  using type = T const;
};
template <typename T>
using add_const_t = typename add_const<T>::type;

template <typename T>
struct is_lvalue_reference : public false_type {};
template <typename T>
struct is_lvalue_reference<T &> : public true_type {};

// Clang and gcc provide builtins for is_same
template <typename T, typename U>
struct is_same : public bool_constant<__is_same_as(T, U)> {};
template <typename T, typename U>
inline constexpr bool is_same_v = __is_same_as(T, U);

// enable_if
template <bool, typename T = void>
struct enable_if {};
template <typename T>
struct enable_if<true, T> {
  using type = T;
};
template <bool Cond, typename T = void>
using enable_if_t = typename enable_if<Cond, T>::type;

// is_standard_layout
template <typename T>
struct is_standard_layout : public bool_constant<__is_standard_layout(T)> {};
template <typename T>
inline constexpr bool is_standard_layout_v = __is_standard_layout(T);

} // namespace asel
