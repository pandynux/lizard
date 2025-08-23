#include "board_fix.h"
#include "board_config.hpp"
#include "ui/lvgl_ui.hpp"
#include "display/display_driver.hpp"

extern "C" void app_main(void)
{
    ui::init();

    while (true) {
        ui::loop();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
