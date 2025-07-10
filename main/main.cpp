#include "board_config.hpp"
#include "display/display_driver.hpp"
#include "ui/lvgl_ui.hpp"

extern "C" void app_main(void)
{
    display_init();
    ui::init();

    while (true) {
        ui::loop();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
