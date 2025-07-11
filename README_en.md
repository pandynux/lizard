# ESP32-S3 LVGL + LovyanGFX Multi-Board Demo

This ESP-IDF C++ project controls Waveshare ESP32-S3 touchscreen displays (3.5", 5", 7", 7" type B) with **LovyanGFX** (fast graphics driver) and **LVGL** (modern GUI) across multiple boards, with **GT911** touch support via LovyanGFX.

## Prerequisites

- ESP-IDF v5.x installed: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/
- Python 3.7+
- Git
- Waveshare ESP32-S3 board

## Dependencies

The script automatically downloads LovyanGFX (display driver + GT911 touch) into `components/`.

## Build

. $IDF_PATH/export.sh
idf.py set-target esp32s3
idf.py build flash monitor

## Selecting the board

In `main/board_config.hpp` uncomment your board line:
- BOARD_7INCH
- BOARD_7INCH_TYPEB
- BOARD_5INCH
- BOARD_3_5INCH

All C and C++ sources include `board_config.hpp` to obtain the pin definitions for the selected board.

## License

This project is released under the MIT License. See [LICENSE](LICENSE) for details.

## Example interface

The application displays a slider and a button. Moving the slider updates the value shown underneath, and each button press increments a counter displayed at the top of the screen.
