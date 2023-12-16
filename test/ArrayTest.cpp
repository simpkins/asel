// Copyright (c) 2023, Adam Simpkins
#include "asel/array.h"

#include "asel/test/TestCase.h"
#include "asel/test/checks.h"

namespace asel {

ASEL_TEST(array, to_array) {
  asel::array c(asel::to_array<short>({3, 2, 1}));
  static_assert(c.size() == 3, "wrong size");
  ASEL_EXPECT_EQ(c[0], 3);
  ASEL_EXPECT_EQ(c[1], 2);
  ASEL_EXPECT_EQ(c[2], 1);
}

} // namespace asel
