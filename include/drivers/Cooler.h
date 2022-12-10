/**
 * @file Cooler.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Controlador de ventilador de 12 volts y 5 milímteros.
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _COOLER_H_
#define _COOLER_H_
#include "mbed.h"
#include "system_settings.h"
class Cooler
{
public:
    Cooler(PinName power_pin, PinName speed_measurement_pin);
    void turn_on(float duty_cycle = 1.0);
    void turn_off();
    size_t get_rotation();
    void count_rotation();
    bool is_on()
    {
        return _is_on;
    }

private:
    bool _is_on = false;
    unsigned long int rotations_in_sample_period = 0;
    PwmOut power_pin;
    InterruptIn speed_measurement_pin;
    float current_duty_cycle = 0;
    float current_RPS = 0;
};
#endif