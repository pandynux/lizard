#include "display_driver.hpp"
#include "board_config.hpp"
#include <LovyanGFX.hpp>

// Exemple d'instance LovyanGFX
class LGFX : public lgfx::LGFX_Device {
public:
    LGFX() {
        // À compléter : configurer selon les pins de board_config.hpp
    }
};

static LGFX lcd;

namespace display {
    void init() {
        lcd.init();
        lcd.setBrightness(128);
        lcd.fillScreen(TFT_BLACK);
    }
}