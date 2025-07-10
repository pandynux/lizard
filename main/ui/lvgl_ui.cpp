#include "lvgl_ui.hpp"
#include "display/display_driver.hpp"
#include "board_config.hpp"
#include <lvgl.h>
#define LVGL_TICK_PERIOD_MS 5
static void lvgl_touch_read(lv_indev_drv_t *drv, lv_indev_data_t *data) {
    auto lcd = get_lcd();
    uint16_t x, y;
    if (lcd->getTouch(&x, &y)) {
        data->point.x = x;
        data->point.y = y;
        data->state = LV_INDEV_STATE_PR;
    } else {
        data->state = LV_INDEV_STATE_REL;
    }
}
static void lv_tick_task(void *arg) {
    while (1) {
        lv_tick_inc(LVGL_TICK_PERIOD_MS);
        vTaskDelay(pdMS_TO_TICKS(LVGL_TICK_PERIOD_MS));
    }
}
namespace ui {
    void init() {
        lv_init();
        display_init();
        static lv_disp_draw_buf_t draw_buf;
        static lv_color_t *buf1 = (lv_color_t*)heap_caps_malloc(LCD_WIDTH * 40 * sizeof(lv_color_t), MALLOC_CAP_DMA);
        static lv_color_t *buf2 = (lv_color_t*)heap_caps_malloc(LCD_WIDTH * 40 * sizeof(lv_color_t), MALLOC_CAP_DMA);
        lv_disp_draw_buf_init(&draw_buf, buf1, buf2, LCD_WIDTH * 40);
        static lv_disp_drv_t disp_drv;
        lv_disp_drv_init(&disp_drv);
        disp_drv.flush_cb = display_lvgl_flush;
        disp_drv.draw_buf = &draw_buf;
        disp_drv.hor_res = LCD_WIDTH;
        disp_drv.ver_res = LCD_HEIGHT;
        lv_disp_drv_register(&disp_drv);
        static lv_indev_drv_t indev_drv;
        lv_indev_drv_init(&indev_drv);
        indev_drv.type = LV_INDEV_TYPE_POINTER;
        indev_drv.read_cb = lvgl_touch_read;
        lv_indev_drv_register(&indev_drv);
        xTaskCreatePinnedToCore(lv_tick_task, "lv_tick", 2048, NULL, 1, NULL, 1);
        lv_obj_t *label = lv_label_create(lv_scr_act());
        lv_label_set_text_fmt(label, "Hello ESP32-S3\n%s", BOARD_NAME);
        lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    }
    void loop() {
        lv_timer_handler();
    }
}
