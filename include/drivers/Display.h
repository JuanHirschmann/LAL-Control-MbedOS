/**
 * @file Display.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Controlador de LCD hd44780 por interfaz I2C
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _DISPLAY_H
#define _DISPLAY_H
#include "Wire.h"
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>
#include "display_settings.h"
/**
 * @brief Clase Display, internamente utiliza la clase hd44780ioClass para resolver
 * la interfaz i2c con el monitor.
 *
 */
class Display
{
public:
    /**
     * @brief Método para inicializar el objeto, sólo se puede luego o en setup().
     *
     */
    void init();
    /**
     * @brief Construye un nuevo objecto Display
     *
     */
    Display();
    /**
     * @brief Fija el valor de temperatura a actualizar (no la imprime en pantalla), la ubicación se da con
     * las constantes de offset de temperatura definidas en display_settings.h
     *
     * @param new_temperature Nueva temperatura a fijar.
     */
    void set_temp(float new_temperature);
    /**
     * @brief Fija el valor del porcentaje de velocidad, no lo imprie en pantalla. La ubicación se da con
     * las constantes de offset de temperatura definidas en display_settings.h
     *
     * @param new_speed_pct Nuevo valor a fijar
     */
    void set_fan_speed_pct(int new_speed_pct);
    /**
     * @brief Fija el el texto a actualizar, no lo imprime en pantalla. La ubicación se da con
     * las constantes de offset de temperatura definidas en display_settings.h
     *
     * @param string_out Nuevo texto a fijar, no puede exceder el máximo establecido en display_settings.h
     */
    void set_text(const char *string_out);
    /**
     * @brief Actualiza los valores en pantalla con los parámetros previamente fijados. Solo actualiza la pantalla
     * cuando uno o más valores hayan cambiado.
     *
     */
    void update();
    /**
     * @brief limpia los caracteres de la pantalla y apaga la retroiluminación, no inhibe la escritura en pantalla.
     *
     */
    void turn_off();
    /**
     * @brief Enciende la retroiluminación y limpia los caracteres de la pantalla.
     *
     */
    void turn_on();

private:
    /**
     * @brief Objeto hd44780_I2Cexp
     *
     */
    hd44780_I2Cexp screen_interface;
    /**
     * @brief variable para saber cuando es necesario actualizar la pantalla con nuevos valores.
     *
     */
    bool update_needed = false;
    char on_screen_text[MAX_DISPLAY_STRING_LENGTH];
    /**
     * @brief Medición de temperatura visualizada en pantalla
     *
     */
    float on_screen_temp = 0.0;
    /**
     * @brief Velocidad del ventilador visualizada en pantalla. 100 es máxima velocidad, 0 es apagado.
     *
     */
    int on_screen_fan_speed_pct = 0; // Porcentaje de velocidad en el ventilador (100 es máximo, 0 es apagado)
};
#endif