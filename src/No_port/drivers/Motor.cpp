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
Motor::Motor(int motor_pin) // Tiene que tener pwm en el pinout
{
    pinMode(motor_pin, OUTPUT);
    this->motor_pin = motor_pin;
}
void Motor::turn_on()
{
    this->is_on = true;
    digitalWrite(this->motor_pin, HIGH);
};
void Motor::turn_off()
{
    this->is_on = false;
    digitalWrite(this->motor_pin, LOW);
};
bool Motor::is_active()
{
    return this->is_on;
};