#include "board_config.hpp"
#include "ui/lvgl_ui.hpp"
#include "display/display_driver.hpp"
#include <esp_err.h>
#include <stdio.h>

extern "C" void app_main(void)
{
    esp_err_t err = ui::init();
    if (err != ESP_OK) {
        printf("LVGL initialization failed: %s\n", esp_err_to_name(err));
        return;
    }

    while (true) {
        ui::loop();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
