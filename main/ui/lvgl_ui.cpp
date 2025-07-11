#include "lvgl_ui.hpp"
#include "display/display_driver.hpp"
#include "board_config.hpp"
#include <lvgl.h>
#include <stdio.h>
#include <stdlib.h>
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
        if (!buf1) {
            printf("Failed to allocate LVGL buffer 1\n");
            abort();
        }
        static lv_color_t *buf2 = (lv_color_t*)heap_caps_malloc(LCD_WIDTH * 40 * sizeof(lv_color_t), MALLOC_CAP_DMA);
        if (!buf2) {
            printf("Failed to allocate LVGL buffer 2\n");
            abort();
        }
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
        static lv_obj_t *info_label;
        static lv_obj_t *slider_label;
        static lv_obj_t *switch_label;
        static lv_obj_t *dropdown_label;
        static lv_obj_t *checkbox_label;
        info_label = lv_label_create(lv_scr_act());
        lv_label_set_text_fmt(info_label, "Hello ESP32-S3\n%s", BOARD_NAME);
        lv_obj_align(info_label, LV_ALIGN_TOP_MID, 0, 20);

        /* Slider with event callback */
        lv_obj_t *slider = lv_slider_create(lv_scr_act());
        lv_slider_set_range(slider, 0, 100);
        lv_obj_align(slider, LV_ALIGN_CENTER, 0, 0);

        slider_label = lv_label_create(lv_scr_act());
        lv_label_set_text(slider_label, "Slider: 0");
        lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

        auto slider_event = [](lv_event_t *e){
            lv_obj_t *slider = lv_event_get_target(e);
            int32_t val = lv_slider_get_value(slider);
            lv_label_set_text_fmt(slider_label, "Slider: %d", val);
        };
        lv_obj_add_event_cb(slider, slider_event, LV_EVENT_VALUE_CHANGED, NULL);

        /* Button to demonstrate touch events */
        lv_obj_t *btn = lv_btn_create(lv_scr_act());
        lv_obj_align(btn, LV_ALIGN_BOTTOM_MID, 0, -20);
        lv_obj_t *btn_label = lv_label_create(btn);
        lv_label_set_text(btn_label, "Press me");
        auto btn_event = [](lv_event_t *e){
            static uint32_t cnt = 0;
            cnt++;
            lv_label_set_text_fmt(info_label, "Button pressed %d", cnt);
        };
        lv_obj_add_event_cb(btn, btn_event, LV_EVENT_CLICKED, NULL);

        /* Switch widget */
        lv_obj_t *sw = lv_switch_create(lv_scr_act());
        lv_obj_align(sw, LV_ALIGN_CENTER, 80, 0);

        switch_label = lv_label_create(lv_scr_act());
        lv_label_set_text(switch_label, "Switch: OFF");
        lv_obj_align_to(switch_label, sw, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

        auto sw_event = [](lv_event_t *e){
            lv_obj_t *sw = lv_event_get_target(e);
            bool state = lv_obj_has_state(sw, LV_STATE_CHECKED);
            lv_label_set_text_fmt(switch_label, "Switch: %s", state ? "ON" : "OFF");
        };
        lv_obj_add_event_cb(sw, sw_event, LV_EVENT_VALUE_CHANGED, NULL);

        /* Drop-down menu */
        lv_obj_t *dd = lv_dropdown_create(lv_scr_act());
        lv_dropdown_set_options(dd, "Item 1\nItem 2\nItem 3");
        lv_obj_align(dd, LV_ALIGN_TOP_RIGHT, -10, 40);

        dropdown_label = lv_label_create(lv_scr_act());
        lv_label_set_text(dropdown_label, "Selected: Item 1");
        lv_obj_align_to(dropdown_label, dd, LV_ALIGN_OUT_BOTTOM_RIGHT, 0, 10);

        auto dd_event = [](lv_event_t *e){
            lv_obj_t *dd = lv_event_get_target(e);
            char buf[16];
            lv_dropdown_get_selected_str(dd, buf, sizeof(buf));
            lv_label_set_text_fmt(dropdown_label, "Selected: %s", buf);
        };
        lv_obj_add_event_cb(dd, dd_event, LV_EVENT_VALUE_CHANGED, NULL);

        /* Checkbox widget */
        lv_obj_t *cb = lv_checkbox_create(lv_scr_act());
        lv_checkbox_set_text(cb, "Accept");
        lv_obj_align(cb, LV_ALIGN_CENTER, -80, 0);

        checkbox_label = lv_label_create(lv_scr_act());
        lv_label_set_text(checkbox_label, "Checkbox: OFF");
        lv_obj_align_to(checkbox_label, cb, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

        auto cb_event = [](lv_event_t *e){
            lv_obj_t *cb = lv_event_get_target(e);
            bool state = lv_obj_has_state(cb, LV_STATE_CHECKED);
            lv_label_set_text_fmt(checkbox_label, "Checkbox: %s", state ? "ON" : "OFF");
        };
        lv_obj_add_event_cb(cb, cb_event, LV_EVENT_VALUE_CHANGED, NULL);
    }
    void loop() {
        lv_timer_handler();
    }
}
