// Copyright (c) 2023, Adam Simpkins
#include "asel/esp/EspError.h"
#include "asel/test/TestCase.h"
#include "asel/test/checks.h"

namespace asel {

ASEL_TEST(EspError, test) {
  auto err1 = make_esp_error(ESP_OK);
  ASEL_EXPECT_FALSE(err1);

  auto err2 = make_esp_error(ESP_ERR_INVALID_ARG);
  ASEL_EXPECT_TRUE(err2);
}

} // namespace asel
