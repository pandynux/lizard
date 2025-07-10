#include "board_config.hpp"
#include "display/display_driver.hpp"
#include "ui/lvgl_ui.hpp"

extern "C" void app_main(void)
{
    // Initialisation du driver d'écran (LovyanGFX)
    display::init();

    // Initialisation LVGL
    ui::init();

    // Boucle principale LVGL
    while (true) {
        ui::loop();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}