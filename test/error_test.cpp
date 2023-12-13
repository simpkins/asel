// Copyright (c) 2023, Adam Simpkins
#include "asel/esp/EspError.h"
#include "asel/test/TestCase.h"

namespace asel {

ASEL_TEST(EspError, test) {
  auto err = make_esp_error(ESP_OK);
  if (err) {
    printf("err is true\n");
  } else {
    printf("err is false\n");
  }

  return {};
}

} // namespace asel
