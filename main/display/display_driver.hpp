#pragma once
#include <LovyanGFX.hpp>
#include <lvgl.h>
lgfx::LGFX_Device* get_lcd();
void display_init();
void display_lvgl_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
