// Copyright (c) 2023, Adam Simpkins
#include "asel/range.h"

#include "asel/test/TestCase.h"
#include "asel/test/checks.h"

namespace asel {

ASEL_TEST(range, construct_from_array) {
  static constexpr std::array<int, 3> ia = {{4, 5, 6}};
  static constexpr asel::range<int const> ra(ia);
  static_assert(ra.size() == 3, "wrong size");

  std::array<int, 4> ia2 = {{7, 8, 9, 10}};
  asel::range<int> ra2(ia2);
  ASEL_EXPECT_EQ(ra2.size(), 4);
}

} // namespace asel
