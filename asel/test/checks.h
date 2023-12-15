// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/log.h"
#include "asel/preproc.h"
#include "asel/test/TestResult.h"
#include "asel/type_traits.h"

/*
 * ASEL_EXPECT_*() checks verify that the specified condition is true.
 * If the check fails they log a failure message and mark the test as a
 * failure, but allow the remainder of the test to continue executing.
 *
 * ASEL_EXPECT_*() checks themselves evaluate to a boolean indicating if the
 * check succeeded or failed.  This makes it possible to use them to record a
 * failure message, and still do your own control flow afterwards based on the
 * result.
 *
 * ASEL_ASSERT_*() checks are similar to ASEL_EXPECT_*(), but also return from
 * the current function if the check fails.  The function return type must be
 * void.  (It does seem rather unfortunate to have a macro that returns from
 * the calling function.  However, this is also how googletest behaves, and so
 * there is plenty of precedent for this behavior.  It seems to work out okay
 * enough, and only occasionally causes some minor confusion when used inside
 * helper functions that are not the top-level test function.)
 */

#define ASEL_EXPECT_TRUE(expr) ASEL_EXPECT_BOOL_(expr, true)
#define ASEL_EXPECT_FALSE(expr) ASEL_EXPECT_BOOL_(expr, false)
#define ASEL_ASSERT_TRUE(expr) ASEL_ASSERT_BOOL_(expr, true)
#define ASEL_ASSERT_FALSE(expr) ASEL_ASSERT_BOOL_(expr, false)

#define ASEL_EXPECT_EQ(a, b) ASEL_EXPECT_CMP_(a, b, ::asel::test_cmp_eq, "==")
#define ASEL_EXPECT_NE(a, b) ASEL_EXPECT_CMP_(a, b, ::asel::test_cmp_ne, "!=")
#define ASEL_EXPECT_GT(a, b) ASEL_EXPECT_CMP_(a, b, ::asel::test_cmp_gt, ">")
#define ASEL_EXPECT_GE(a, b) ASEL_EXPECT_CMP_(a, b, ::asel::test_cmp_ge, ">=")
#define ASEL_EXPECT_LT(a, b) ASEL_EXPECT_CMP_(a, b, ::asel::test_cmp_lt, "<")
#define ASEL_EXPECT_LE(a, b) ASEL_EXPECT_CMP_(a, b, ::asel::test_cmp_le, "<=")

#define ASEL_ASSERT_EQ(a, b) ASEL_ASSERT_CMP_(a, b, ::asel::test_cmp_eq, "==")
#define ASEL_ASSERT_NE(a, b) ASEL_ASSERT_CMP_(a, b, ::asel::test_cmp_ne, "!=")
#define ASEL_ASSERT_GT(a, b) ASEL_ASSERT_CMP_(a, b, ::asel::test_cmp_gt, ">")
#define ASEL_ASSERT_GE(a, b) ASEL_ASSERT_CMP_(a, b, ::asel::test_cmp_ge, ">=")
#define ASEL_ASSERT_LT(a, b) ASEL_ASSERT_CMP_(a, b, ::asel::test_cmp_lt, "<")
#define ASEL_ASSERT_LE(a, b) ASEL_ASSERT_CMP_(a, b, ::asel::test_cmp_le, "<=")

#define ASEL_ADD_FAILURE(msg, ...)                                             \
  do {                                                                         \
    ::asel::g_test_result->add_failure();                                      \
    ::asel::log_message(__FILE__, ":", __LINE__, ": failure: ", msg,           \
                        ##__VA_ARGS__);                                        \
  } while (0)

// We use an immediately-invoked lambda so that we can have a multi-statement
// macro body but still have the macro behave like a single expression.
#define ASEL_EXPECT_BOOL_(expr, expected)                                      \
  ([&]() {                                                                     \
    if (static_cast<bool>(expr) != expected) {                                 \
      ASEL_ADD_FAILURE(                                                        \
          "expected " ASEL_STRINGIFY(expr) " to be " ASEL_STRINGIFY(           \
              expected) "; value: ",                                           \
          expr);                                                               \
      return false;                                                            \
    }                                                                          \
    return true;                                                               \
  }())

#define ASEL_ASSERT_BOOL_(expr, expected)                                      \
  do {                                                                         \
    if (!ASEL_EXPECT_BOOL_(expr, expected)) {                                  \
      return;                                                                  \
    }                                                                          \
  } while (0)

#define ASEL_EXPECT_CMP_(a, b, cmp_op, op_str)                                 \
  ([&]() {                                                                     \
    if (!cmp_op(a, b)) {                                                       \
      ASEL_ADD_FAILURE("expected " ASEL_STRINGIFY(                             \
                           a) " " op_str " " ASEL_STRINGIFY(b) " ; actual: ",  \
                       (a), " vs ", (b));                                      \
      return false;                                                            \
    }                                                                          \
    return true;                                                               \
  }())

#define ASEL_ASSERT_CMP_(a, b, cmp_op, op_str)                                 \
  do {                                                                         \
    if (!ASEL_EXPECT_CMP_(a, b, cmp_op, op_str)) {                             \
      return;                                                                  \
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

// Define test_cmp_ne as a neibloid.
// It should not be customizable, and should behave exactly the opposite of
// test_cmp_eq()
inline constexpr struct TestCmpNE {
  template <typename T, typename U> constexpr bool operator()(T &&t, U &&u) {
    return !test_cmp_eq(asel::forward<T>(t), asel::forward<U>(u));
  }
} test_cmp_ne{};

template <typename T, typename U>
constexpr bool test_cmp_gt(const T &t, const U &u) {
  return t > u;
}

template <typename T, typename U>
constexpr bool test_cmp_ge(const T &t, const U &u) {
  return t >= u;
}

// Define test_cmp_lt as a neibloid.
// It should not be customizable, and should behave exactly the opposite of
// test_cmp_ge()
inline constexpr struct TestCmpLT {
  template <typename T, typename U> constexpr bool operator()(T &&t, U &&u) {
    return !test_cmp_ge(asel::forward<T>(t), asel::forward<U>(u));
  }
} test_cmp_lt{};

// Define test_cmp_le as a neibloid.
// It should not be customizable, and should behave exactly the opposite of
// test_cmp_gt()
inline constexpr struct TestCmpLE {
  template <typename T, typename U> constexpr bool operator()(T &&t, U &&u) {
    return !test_cmp_gt(asel::forward<T>(t), asel::forward<U>(u));
  }
} test_cmp_le{};

} // namespace asel
