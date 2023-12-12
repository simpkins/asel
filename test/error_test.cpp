// Copyright (c) 2023, Adam Simpkins
#include "asel/esp/EspError.h"

namespace asel {

void test_error() {
  auto err = make_esp_error(ESP_OK);
  if (err) {
    printf("err is true\n");
  } else {
    printf("err is false\n");
  }
}

} // namespace asel
