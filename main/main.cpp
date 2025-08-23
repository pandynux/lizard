#include "board_config.hpp"
#include "display/display_driver.hpp"
#include "ui/lvgl_ui.hpp"
#include <esp_err.h>
#include <esp_log.h>

static const char *TAG = "main";

extern "C" void app_main(void) {
  esp_err_t err = ui::init();
  if (err != ESP_OK) {
    ESP_LOGE(TAG, "LVGL initialization failed: %s", esp_err_to_name(err));
    return;
  }

  while (true) {
    ui::loop();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}
