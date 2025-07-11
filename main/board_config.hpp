#pragma once
// La sélection de la carte se fait dans `idf.py menuconfig` via les options
// CONFIG_BOARD_*. Aucune modification manuelle de ce fichier n'est nécessaire.

#if defined(CONFIG_BOARD_7INCH)
#include "board/board_7inch.hpp"
#elif defined(CONFIG_BOARD_7INCH_TYPEB)
#include "board/board_7inch_typeb.hpp"
#elif defined(CONFIG_BOARD_5INCH)
#include "board/board_5inch.hpp"
#elif defined(CONFIG_BOARD_3_5INCH)
#include "board/board_3_5inch.hpp"
#else
#error "Aucune carte sélectionnée ! Configurez CONFIG_BOARD_xxx dans menuconfig"
#endif
