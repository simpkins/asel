// Copyright (c) 2023, Adam Simpkins
#include "asel/test/run_tests.h"

#include "asel/test/TestCase.h"
#include "asel/test/TestRegistry.h"

namespace asel {

void run_tests() {
  auto *test = g_test_registry.head;
  size_t n = 0;
  while (test) {
    ++n;
    printf("Running %s.%s\n", test->suite, test->name);
    test->run();
    test = test->next;
  }

  printf("Ran %zu tests\n", n);
}

} // namespace asel
