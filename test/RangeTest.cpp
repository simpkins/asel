// Copyright (c) 2023, Adam Simpkins
#include "asel/range.h"

#include "asel/test/TestCase.h"
#include "asel/test/checks.h"

namespace asel {

ASEL_TEST(range, construct_from_array) {
  static constexpr array<int, 3> ia = {{4, 5, 6}};
  static constexpr asel::range<int const> ra(ia);
  static_assert(ra.size() == 3, "wrong size");
  static_assert(ra[0] == 4, "wrong value for ra[0]");
  static_assert(ra[1] == 5, "wrong value for ra[5]");
  static_assert(ra[2] == 6, "wrong value for ra[6]");

  array<int, 4> ia2 = {{7, 8, 9, 10}};
  asel::range<int> ra2(ia2);
  ASEL_EXPECT_EQ(ra2.size(), 4);
  ASEL_EXPECT_EQ(ra2[0], 7);
  ASEL_EXPECT_EQ(ra2[1], 8);
  ASEL_EXPECT_EQ(ra2[2], 9);
  ASEL_EXPECT_EQ(ra2[3], 10);
}

} // namespace asel
