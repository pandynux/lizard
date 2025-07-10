#include "lvgl_ui.hpp"
#include <lvgl.h>

namespace ui {
    void init() {
        lv_init();
        // À compléter : initialisation des buffers, drivers, tick, etc.
        // Exemple simple :
        lv_obj_t *label = lv_label_create(lv_scr_act());
        lv_label_set_text(label, "Hello, LVGL + LovyanGFX!");
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }

    void loop() {
        lv_timer_handler(); // LVGL handler
    }
}