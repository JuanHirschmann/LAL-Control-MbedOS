#ifndef BINARY_LED_H
#define BINARY_LED_H

#include <mbed.h>
#include "types.h"
/**
 * @brief Clase para el manejo de un indicador LED RG.
 *
 */
class Digital_dual_LED
{
public:
    /**
     * @brief Construye un nuevo objecto Dual_LED
     *
     * @param green_led_pin pin donde el led verde esta conectado
     * @param red_led_pin pin donde el led rojo esta conectado
     */
    Digital_dual_LED(PinName green_led_pin, PinName red_led_pin);
    /**
     * @brief Fija el color del led, no enciende el led,
     *
     * @param new_color
     */
    void turn_red();
    /**
     * @brief Enciende el LED en verde.
     *
     */
    void turn_green();

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
     * @brief pin asociado al LED verde
     *
     */
    DigitalOut green_led;
    /**
     * @brief pin asociado al led rojo.
     *
     */
    DigitalOut red_led;
};
#endif
