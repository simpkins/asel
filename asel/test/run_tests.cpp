// Copyright (c) 2023, Adam Simpkins
#include "asel/test/run_tests.h"

#include "asel/test/TestCase.h"
#include "asel/test/TestRegistry.h"

#include <cstdio>

namespace asel {

TestResult* g_test_result;

unsigned int run_tests() {
  auto *test = g_test_registry.head;
  unsigned int num_tests = 0;
  unsigned int failed_tests = 0;
  while (test) {
    ++num_tests;
    fprintf(stderr, "Running %s.%s\n", test->suite, test->name);
    g_test_result = &test->result;
    g_test_result->reset();

    test->run();
    test = test->next;

    if (g_test_result->num_failures() > 0) {
      fprintf(stderr, "  Failed\n");
      ++failed_tests;
    } else {
      fprintf(stderr, "  Success\n");
    }
  }

  if(failed_tests == 0) {
    fprintf(stderr, "Ran %u tests\n", num_tests);
    fprintf(stderr, "100%% successful\n");
  } else {
    fprintf(stderr, "%u of %u tests failed\n", failed_tests, num_tests);
  }
  return failed_tests;
}

} // namespace asel
