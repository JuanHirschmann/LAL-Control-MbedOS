/**
 * @file display_settings.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Archivo de configuración de la pantalla
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef DISPLAY_SETTINGS_H
#define DISPLAY_SETTINGS_H
const int MAX_DISPLAY_STRING_LENGTH = 60;
const char CELSIUS_CHARACTER = 223;
const char PERCENTAGE_SIGN = 37;
const int LCD_DISPLAY_RESOLUTION[2] = {20, 4};
const int TEMP_INDICATOR_CURSOR_OFFSET[] = {0, 3};
const int FAN_INDICATOR_CURSOR_OFFSET[] = {10, 3};
const int HIGH_BRIGHTNESS_LEVEL = 255;
const int LOW_BRIGHTNESS_LEVEL = 128;
#endif