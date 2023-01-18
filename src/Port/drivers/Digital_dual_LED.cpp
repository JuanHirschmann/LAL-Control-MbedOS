/**
 * @file Digital_dual_LED.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Implementación de Digital_dual_LED.h
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "drivers/Digital_dual_LED.h"
Digital_dual_LED::Digital_dual_LED(PinName green_led_pin, PinName red_led_pin) : green_led(green_led_pin), red_led(red_led_pin){};

void Digital_dual_LED::turn_red()
{
    this->green_led.write(0);
    this->red_led.write(1);
}
void Digital_dual_LED::turn_green()
{
    this->green_led.write(1);
    this->red_led.write(0);
}

void Digital_dual_LED::turn_off()
{
    this->is_on = false;
    this->green_led.write(0);
    this->red_led.write(0);
}