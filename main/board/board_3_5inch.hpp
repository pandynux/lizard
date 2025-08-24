#pragma once

// Utilisation de 'static constexpr' pour les constantes en C++.
// C'est plus sûr (typage fort) et plus moderne que les macros #define.
namespace board_3_5inch {
    static constexpr const char* BOARD_NAME = "Waveshare ESP32-S3-Touch-LCD-3.5B";
    static constexpr int LCD_WIDTH  = 320;
    static constexpr int LCD_HEIGHT = 480;
    static constexpr int LCD_MOSI   = 47;
    static constexpr int LCD_CLK    = 21;
    static constexpr int LCD_CS     = 15;
    static constexpr int LCD_DC     = 14;
    static constexpr int LCD_RST    = 13;
    static constexpr int LCD_BL     = 2;
    static constexpr int TOUCH_SDA  = 18;
    static constexpr int TOUCH_SCL  = 8;
    static constexpr int TOUCH_INT  = 16;
    static constexpr int GT911_I2C_ADDR = 0x5D;
}
