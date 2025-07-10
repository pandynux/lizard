#pragma once

// Sélection de la carte cible via define (à automatiser par menuconfig par la suite)
// #define BOARD_7INCH
// #define BOARD_5INCH
// #define BOARD_3_5INCH
// #define BOARD_7INCH_TYPEB

#if defined(BOARD_7INCH)
#include "board/board_7inch.hpp"
#elif defined(BOARD_5INCH)
#include "board/board_5inch.hpp"
#elif defined(BOARD_3_5INCH)
#include "board/board_3_5inch.hpp"
#elif defined(BOARD_7INCH_TYPEB)
#include "board/board_7inch_typeb.hpp"
#else
#error "Aucune carte définie ! Définissez BOARD_xxx dans board_config.hpp"
#endif