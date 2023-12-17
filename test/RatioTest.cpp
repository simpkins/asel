// Copyright (c) 2023, Adam Simpkins
#include "asel/ratio.h"

#include "asel/test/TestCase.h"
#include "asel/test/checks.h"

namespace asel {

ASEL_TEST(Ratio, test) {
  static_assert(ratio<1, 1>::num == 1, "");
  static_assert(ratio<10, 10>::num == 1, "");
  static_assert(ratio<10, 10>::den == 1, "");
  static_assert(ratio<10, 30>::num == 1, "");
  static_assert(ratio<10, 30>::den == 3, "");
  static_assert(ratio<30, -20>::num == -3, "");
  static_assert(ratio<30, -20>::den == 2, "");
}

} // namespace asel
