#include "display_driver.hpp"
#include "board_config.hpp"
#include <lvgl.h>

// Utilisation de l'espace de noms de la carte sélectionnée
#if defined(CONFIG_BOARD_7INCH)
using namespace board_7inch;
#elif defined(CONFIG_BOARD_7INCH_TYPEB)
using namespace board_7inch_typeb;
#elif defined(CONFIG_BOARD_5INCH)
using namespace board_5inch;
#elif defined(CONFIG_BOARD_3_5INCH)
using namespace board_3_5inch;
#endif

class LGFX : public lgfx::LGFX_Device {
    lgfx::Bus_Parallel16 _bus_instance;
    lgfx::Panel_ST7796 _panel_instance;
    lgfx::Touch_GT911 _touch_instance;

public:
    LGFX() {
        {
            auto cfg = _bus_instance.config();
            cfg.freq_write = 20000000;
            cfg.pin_wr = LCD_CLK;
            cfg.pin_rd = -1;
            cfg.pin_rs = LCD_DC;
            cfg.pin_d0 = LCD_MOSI; // Correction du nom de la broche
            _bus_instance.config(cfg);
            _panel_instance.setBus(&_bus_instance);
        }
        {
            auto cfg = _panel_instance.config();
            cfg.pin_cs = LCD_CS;
            cfg.pin_rst = LCD_RST;
            cfg.pin_busy = -1;
            cfg.memory_width = LCD_WIDTH;
            cfg.memory_height = LCD_HEIGHT;
            cfg.panel_width = LCD_WIDTH;
            cfg.panel_height = LCD_HEIGHT;
            cfg.offset_x = 0;
            cfg.offset_y = 0;
            _panel_instance.config(cfg);
        }
        {
             auto blk = _panel_instance.config_light();
            blk.pin_bl = LCD_BL;
            blk.invert = false;
            blk.freq = 44100;
            blk.pwm_channel = 7;
            _panel_instance.config_light(blk);
        }
        {
            auto cfg = _touch_instance.config();
            cfg.x_min = 0;
            cfg.x_max = LCD_WIDTH - 1;
            cfg.y_min = 0;
            cfg.y_max = LCD_HEIGHT - 1;
            cfg.pin_int = TOUCH_INT;
            cfg.bus_shared = true;
            cfg.i2c_port = I2C_NUM_0;
            cfg.pin_sda = TOUCH_SDA;
            cfg.pin_scl = TOUCH_SCL;
            cfg.freq = 400000;
            cfg.i2c_addr = GT911_I2C_ADDR;
            _touch_instance.config(cfg);
            _panel_instance.setTouch(&_touch_instance);
        }
        setPanel(&_panel_instance);
    }
};

static LGFX lcd;
uint8_t display_brightness = 192;

lgfx::LGFX_Device *get_lcd() { return &lcd; }

void display_init() {
    if (!lcd.init()) {
        LV_LOG_ERROR("LGFX initialization failed!");
        while (1) {
            vTaskDelay(1);
        }
    }
    lcd.setBrightness(display_brightness);
    lcd.fillScreen(TFT_BLACK);
}


void display_lvgl_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    int32_t w = area->x2 - area->x1 + 1;
    int32_t h = area->y2 - area->y1 + 1;
    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.pushColors((lgfx::rgb565_t *)px_map, w * h, true);
    lcd.endWrite();
    lv_display_flush_ready(disp);
}

