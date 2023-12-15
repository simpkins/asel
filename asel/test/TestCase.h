// Copyright (c) 2023, Adam Simpkins
#pragma once

#include "asel/preproc.h"
#include "asel/test/TestResult.h"

#define ASEL_TEST_CLASS_NAME(suite, name) ASEL_CONCAT4(Test_, suite, _, name)

#define ASEL_TEST(suite, name)                                                 \
  class ASEL_TEST_CLASS_NAME(suite, name) : public ::asel::TestCase {          \
  public:                                                                      \
    ASEL_TEST_CLASS_NAME(suite, name)                                          \
    () : ::asel::TestCase(ASEL_STRINGIFY(suite), ASEL_STRINGIFY(name)) {}      \
                                                                               \
    void run() override;                                                       \
  };                                                                           \
  ASEL_TEST_CLASS_NAME(suite, name) ASEL_UNIQUE_NAME(name);                    \
  void ASEL_TEST_CLASS_NAME(suite, name)::run()

namespace asel {

class TestCase {
public:
  TestCase(); // TODO: delete
  explicit TestCase(const char *suite, const char *name);

  virtual void run() = 0;

  TestCase *next = nullptr;

  const char *const suite = nullptr;
  const char *const name = nullptr;
  TestResult result;
};

} // namespace asel
