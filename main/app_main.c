#include "board_config.h"
#include "lvgl_ui/lvgl_demo.h"
#include "display_drivers/lovyangfx_driver.h"

void app_main(void) {
    // Initialisation du driver d’écran avec les paramètres du board courant
    display_init(LCD_WIDTH, LCD_HEIGHT, /* autres paramètres selon board_config.h */);
    // Initialisation LVGL
    lv_init();
    // ... init buffer, tick, etc.
    lvgl_demo_start(); // Démarrer l’UI de test
    while (1) {
        lv_task_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}