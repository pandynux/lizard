# ESP32-S3 LVGL + LovyanGFX Multi-Board Demo

Ce projet ESP-IDF C++ permet de piloter les écrans tactiles Waveshare ESP32-S3 (3,5", 5", 7", 7" type B) avec **LovyanGFX** (driver graphique rapide) et **LVGL** (UI graphique moderne) sur plusieurs cartes, avec gestion du tactile **GT911** via LovyanGFX.

## Prérequis

- ESP-IDF v5.x installé : https://docs.espressif.com/projects/esp-idf/fr/latest/esp32/get-started/
- Python 3.7+
- Git
- Carte ESP32-S3 Waveshare

## Dépendances

Le script télécharge automatiquement LovyanGFX (driver écran + tactile GT911) dans `components/`.

## Compilation

. $IDF_PATH/export.sh
idf.py set-target esp32s3
idf.py build flash monitor

## Sélection de la carte

Dans `main/board_config.hpp` décommente la ligne de ta carte :
- BOARD_7INCH
- BOARD_7INCH_TYPEB
- BOARD_5INCH
- BOARD_3_5INCH

Toutes les sources C et C++ incluent `board_config.hpp` pour récupérer
les définitions de brochage correspondant à la carte sélectionnée.
