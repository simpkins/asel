// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/log.h"
#include "asel/preproc.h"
#include "asel/test/TestResult.h"

#define ASEL_ADD_FAILURE(msg, ...)                                             \
  do {                                                                         \
    g_test_result->add_failure();                                              \
    ::asel::log_message("failure: ", msg, ##__VA_ARGS__);                      \
  } while (0)

#define ASEL_EXPECT_TRUE(expr)                                                 \
  do {                                                                         \
    if (!expr) {                                                               \
      ASEL_ADD_FAILURE(                                                        \
          "expected " ASEL_STRINGIFY(expr) " to be true; value: ", expr);      \
    }                                                                          \
  } while (0)
#define ASEL_EXPECT_FALSE(expr)                                                \
  do {                                                                         \
    if (expr) {                                                                \
      ASEL_ADD_FAILURE(                                                        \
          "expected " ASEL_STRINGIFY(expr) " to be false; value: ", expr);     \
    }                                                                          \
  } while (0)
