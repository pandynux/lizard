#pragma once

#if defined(CONFIG_BOARD_7INCH)
#include "../config/board_7inch.h"
#elif defined(CONFIG_BOARD_5INCH)
#include "../config/board_5inch.h"
#elif defined(CONFIG_BOARD_3_5INCH)
#include "../config/board_3_5inch.h"
#elif defined(CONFIG_BOARD_7INCH_TYPEB)
#include "../config/board_7inch_typeb.h"
#else
#error "Aucune carte définie!"
#endif