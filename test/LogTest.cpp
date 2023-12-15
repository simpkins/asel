// Copyright (c) 2023, Adam Simpkins
#include "asel/log.h"
#include "asel/test/TestCase.h"

namespace asel {

ASEL_TEST(LogTest, test) {
  // We don't have any checks in this test at the moment.
  // Currently this is present mostly just to make sure that the code
  // compiles.
  int foo = 5;
  asel::log_message("foo: ", foo);
}

} // namespace asel
