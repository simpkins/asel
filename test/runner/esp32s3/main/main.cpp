// Copyright (c) 2023, Adam Simpkins
#include "asel/test/run_tests.h"

#include <cstdio>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

extern "C" void app_main() {
  esp_log_level_set("asel", ESP_LOG_VERBOSE);

  asel::run_tests();
  while (true) {
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
