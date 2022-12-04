/**
 * @file Motor.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief
 * @version 0.1
 * @date 2022-11-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "drivers/Motor.h"
Motor::Motor(PinName motor_pin) : motor_pin(motor_pin) // Tiene que tener pwm en el pinout
{
}
void Motor::turn_on()
{
    this->is_on = true;
    this->motor_pin.write(1);
};
void Motor::turn_off()
{
    this->is_on = false;
    this->motor_pin.write(0);
};
bool Motor::is_active()
{
    return this->is_on;
};