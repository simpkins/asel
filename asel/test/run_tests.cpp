// Copyright (c) 2023, Adam Simpkins
#include "asel/test/run_tests.h"

#include "asel/test/TestCase.h"
#include "asel/test/TestRegistry.h"
#include "asel/log.h"

namespace asel {

TestResult* g_test_result;

unsigned int run_tests() {
  auto *test = g_test_registry.head;
  unsigned int num_tests = 0;
  unsigned int failed_tests = 0;
  while (test) {
    ++num_tests;
    log_message("Running ", test->suite, ".", test->name, "...");
    g_test_result = &test->result;
    g_test_result->reset();

    test->run();
    test = test->next;

    if (g_test_result->num_failures() > 0) {
      log_message("  Failed");
      ++failed_tests;
    } else {
      log_message("  Success");
    }
  }

  if(failed_tests == 0) {
    log_message("Ran ", num_tests, " tests");
    log_message("100% successful");
  } else {
    log_message(failed_tests, " of ", num_tests, " tests failed");
  }
  return failed_tests;
}

} // namespace asel
