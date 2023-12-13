// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/log.h"
#include "asel/preproc.h"
#include "asel/test/TestResult.h"
#include "asel/type_traits.h"

#define ASEL_EXPECT_TRUE(expr) ASEL_EXPECT_BOOL_(expr, true, false)
#define ASEL_EXPECT_FALSE(expr) ASEL_EXPECT_BOOL_(expr, false, false)
#define ASEL_ASSERT_TRUE(expr) ASEL_EXPECT_BOOL_(expr, true, true)
#define ASEL_ASSERT_FALSE(expr) ASEL_EXPECT_BOOL_(expr, false, true)

#define ASEL_EXPECT_EQ(a, b) ASEL_EXPECT_CMP_(a, b, ::asel::test_cmp_eq, "!=", false)
#define ASEL_EXPECT_NE(a, b) ASEL_EXPECT_CMP_(a, b, ::asel::test_cmp_ne, "==", false)
#if 0
#define ASEL_EXPECT_GT(a, b) ASEL_EXPECT_CMP_(a, b, >, "<=", false)
#define ASEL_EXPECT_GE(a, b) ASEL_EXPECT_CMP_(a, b, >=, "<", false)
#define ASEL_EXPECT_LT(a, b) ASEL_EXPECT_CMP_(a, b, <, ">=", false)
#define ASEL_EXPECT_LE(a, b) ASEL_EXPECT_CMP_(a, b, <=, ">", false)

#define ASEL_ASSERT_EQ(a, b) ASEL_EXPECT_CMP_(a, b, ==, "!=", true)
#define ASEL_ASSERT_NE(a, b) ASEL_EXPECT_CMP_(a, b, !=, "==", true)
#define ASEL_ASSERT_GT(a, b) ASEL_EXPECT_CMP_(a, b, >, "<=", true)
#define ASEL_ASSERT_GE(a, b) ASEL_EXPECT_CMP_(a, b, >=, "<", true)
#define ASEL_ASSERT_LT(a, b) ASEL_EXPECT_CMP_(a, b, <, ">=", true)
#define ASEL_ASSERT_LE(a, b) ASEL_EXPECT_CMP_(a, b, <=, ">", true)
#endif

#define ASEL_ADD_FAILURE(msg, ...)                                             \
  do {                                                                         \
    ::asel::g_test_result->add_failure();                                      \
    ::asel::log_message("failure: ", msg, ##__VA_ARGS__);                      \
  } while (0)

#define ASEL_EXPECT_BOOL_(expr, expected, fatal)                               \
  do {                                                                         \
    if (static_cast<bool>(expr) != expected) {                                 \
      ASEL_ADD_FAILURE(                                                        \
          "expected " ASEL_STRINGIFY(expr) " to be " ASEL_STRINGIFY(           \
              expected) "; value: ",                                           \
          expr);                                                               \
      if (fatal) {                                                             \
        return;                                                                \
      }                                                                        \
    }                                                                          \
  } while (0)

#define ASEL_EXPECT_CMP_(a, b, cmp_op, fail_op_str, fatal)                     \
  do {                                                                         \
    if (!cmp_op(a, b)) {                                                       \
      ASEL_ADD_FAILURE(                                                        \
          "expected " ASEL_STRINGIFY(a) " " fail_op_str                        \
                                        " " ASEL_STRINGIFY(b) " ; actual: ",   \
          (a), " vs ", (b));                                                   \
      if (fatal) {                                                             \
        return;                                                                \
      }                                                                        \
    }                                                                          \
  } while (0)

namespace asel {

// TODO: implement test_cmp_eq as a customization point object,
// possibly using tag_invoke
template <typename T, typename U>
constexpr bool test_cmp_eq(const T &t, const U &u) {
  return t == u;
}

constexpr bool test_cmp_eq(buf_view a, buf_view b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t n = 0; n < a.size(); ++n) {
    if (a[n] != b[n]) {
      return false;
    }
  }
  return true;
}

template <size_t N, size_t M>
constexpr bool test_cmp_eq(const std::array<uint8_t, N> &a,
                           const std::array<uint8_t, M> &b) {
  return test_cmp_eq(buf_view(a.data(), a.size()),
                     buf_view(b.data(), b.size()));
}

template <size_t N>
constexpr bool test_cmp_eq(const buf_view &a, const std::array<uint8_t, N> &b) {
  return test_cmp_eq(a, buf_view(b.data(), b.size()));
}

template <size_t N>
constexpr bool test_cmp_eq(const std::array<uint8_t, N> &a, const buf_view &b) {
  return test_cmp_eq(buf_view(a.data(), a.size()), b);
}

inline constexpr struct TestCmpNe {
  template <typename T, typename U> constexpr bool operator()(T &&t, U &&u) {
    return !test_cmp_eq(asel::forward<T>(t), asel::forward<U>(u));
  }
} test_cmp_ne{};

} // namespace asel
