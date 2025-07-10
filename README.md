# ESP32-S3 LVGL + LovyanGFX Demo (Multi-board Waveshare)

Ce projet est une base ESP-IDF C++ pour ESP32-S3 avec écrans tactiles Waveshare supportant LovyanGFX + LVGL.  
Il permet de sélectionner la carte cible via configuration (`main/board_config.hpp`) et supporte plusieurs modèles (7", 5", 3.5", 7" Type B).

## Structure

- `main/board/board_xxx.hpp` : config matérielle par carte
- `main/display/` : drivers écran (LovyanGFX)
- `main/ui/` : interface graphique LVGL
- `main/main.cpp` : point d'entrée

## Utilisation

1. Sélectionner la carte dans `main/board_config.hpp` en décommentant la bonne ligne.
2. Compiler et flasher avec ESP-IDF (`idf.py build flash monitor`).

## À compléter

- Configuration LovyanGFX selon le modèle d'écran
- Initialisation complète des buffers LVGL
- Gestion du tactile (I2C)