/**
 * @file Dual_LED.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Controlador de LED RG.
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef DUAL_LED_H
#define DUAL_LED
#include "Arduino.h"
#include "types.h"
#include "system_settings.h"
/**
 * @brief Clase para el manejo de un indicador LED RG.
 *
 */
class Dual_LED
{
public:
    /**
     * @brief Construye un nuevo objecto Dual_LED
     *
     * @param green_led_pin pin donde el led verde esta conectado
     * @param red_led_pin pin donde el led rojo esta conectado
     */
    Dual_LED(int green_led_pin, int red_led_pin);
    /**
     * @brief Fija el color del led, no enciende el led,
     *
     * @param new_color
     */
    void set_color(COLOR_TYPES new_color);
    /**
     * @brief Enciende el LED en rojo.
     *
     */
    void turn_red();
    /**
     * @brief Enciende el LED en verde.
     *
     */
    void turn_green();
    /**
     * @brief Enciende el LED en amarillo. El comportamiento es indefinido
     * para pines no PWM.
     *
     */
    void turn_yellow();
    /**
     * @brief Enciende el LED en el color actual.
     *
     */
    void turn_on();
    /**
     * @brief Permuta el estado del LED.
     *
     */
    void toggle();
    /**
     * @brief Apaga el LED.
     *
     */
    void turn_off();

private:
    /**
     * @brief variable para el estado del LED
     *
     */
    bool is_on = true;
    /**
     * @brief Variable que almacena el color actual del LED
     *
     */
    COLOR_TYPES current_color = GREEN;
    /**
     * @brief Ciclo de trabajo asociado al LED verde
     *
     */
    float green_led_duty_cycle = 0;
    /**
     * @brief Ciclo de trabajo asociado al LED
     *
     */
    float red_led_duty_cycle = 0;
    /**
     * @brief pin asociado al led verde.
     *
     */
    int green_led_pin = 0;
    /**
     * @brief pin asociado al led rojo.
     *
     */
    int red_led_pin = 0;
};
#endif