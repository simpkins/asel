// Copyright (c) 2023, Adam Simpkins
#pragma once

namespace asel {

class TestResult {
public:
  void reset() {
    num_failures_ = 0;
  }
  void add_failure() {
    ++num_failures_;
  }

  unsigned int num_failures() const {
    return num_failures_;
  }

private:
  unsigned int num_failures_ = 0;
};

// Singleton which will be non-null when running a test
extern TestResult *g_test_result;

} // namespace asel
