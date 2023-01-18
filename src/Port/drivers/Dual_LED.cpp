/**
 * @file Dual_LED.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Implementación de Dual_LED.h
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "drivers/Dual_LED.h"
Dual_LED::Dual_LED(PinName green_led_pin, PinName red_led_pin) : green_led(green_led_pin), red_led(red_led_pin)
{
    green_led.period(0.001);
    red_led.period(0.001);
};
void Dual_LED::set_color(COLOR_TYPES new_color)
{
    this->current_color = new_color;
    switch (new_color)
    {
    case GREEN:
        this->green_led_duty_cycle = GREEN_COLOR_DUTY_CYCLE[0];
        this->red_led_duty_cycle = GREEN_COLOR_DUTY_CYCLE[1];
        break;

    case YELLOW:
        this->green_led_duty_cycle = YELLOW_COLOR_DUTY_CYCLE[0];
        this->red_led_duty_cycle = YELLOW_COLOR_DUTY_CYCLE[1];
        break;

    case RED:
        this->green_led_duty_cycle = RED_COLOR_DUTY_CYCLE[0];
        this->red_led_duty_cycle = RED_COLOR_DUTY_CYCLE[1];
        break;

    default:
        break;
    }
}

void Dual_LED::turn_red()
{
    this->set_color(RED);
    this->turn_on();
}
void Dual_LED::turn_green()
{
    this->set_color(GREEN);
    this->turn_on();
}
void Dual_LED::turn_yellow()
{
    this->set_color(YELLOW);
    this->turn_on();
}
void Dual_LED::turn_on()
{
    this->is_on = true;
    this->green_led.write(this->green_led_duty_cycle);
    this->red_led.write(this->red_led_duty_cycle);
}
void Dual_LED::toggle()
{
    if (this->is_on)
    {
        this->turn_off();
    }
    else
    {
        this->turn_on();
    }
}
void Dual_LED::turn_off()
{
    this->is_on = false;
    this->green_led.write(0);
    this->red_led.write(0);
}