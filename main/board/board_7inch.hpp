#pragma once

// Utilisation de 'static constexpr' pour les constantes en C++.
namespace board_7inch {
    static constexpr const char* BOARD_NAME = "Waveshare ESP32-S3-Touch-LCD-7";
    static constexpr int LCD_WIDTH  = 1024;
    static constexpr int LCD_HEIGHT = 600;
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
