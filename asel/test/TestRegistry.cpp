// Copyright (c) 2023, Adam Simpkins
#include "asel/test/TestRegistry.h"

#include "asel/test/TestCase.h"

namespace asel {

TestRegistry g_test_registry;

void TestRegistry::register_test(TestCase *test) {
  if (head == nullptr) {
    head = test;
    tail = test;
  } else {
    tail->next = test;
    tail = test;
  }
}

} // namespace asel
