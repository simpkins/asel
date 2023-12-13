// Copyright (c) 2023, Adam Simpkins
#include "asel/test/TestCase.h"

#include "asel/test/TestRegistry.h"

namespace asel {

TestCase::TestCase() : suite("undef_suite"), name("undef_name") {
  g_test_registry.register_test(this);
}

TestCase::TestCase(const char *s, const char *n) : suite(s), name(n) {
  g_test_registry.register_test(this);
}

} // namespace asel
