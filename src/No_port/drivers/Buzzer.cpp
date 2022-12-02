/**
 * @file Buzzer.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "drivers/Buzzer.h"
Buzzer::Buzzer(PinName buzzer_pin, unsigned int frequency) : buzzer(buzzer_pin) // Tiene que tener pwm en el pinout
{
    this->buzzer_pin = buzzer_pin;
    this->frequency = frequency;
}
void Buzzer::turn_on(unsigned long duration = 0)
{
    this->is_ringing = true;
    buzzer.period(1 / this->frequency);
    buzzer.write(1);
};
void Buzzer::turn_off()
{
    this->is_ringing = false;
    buzzer.write(0);
};
void Buzzer::toggle(unsigned int duration = 0)
{
    if (!this->is_ringing)
    {
        this->turn_on(duration);
    }
    else
    {
        this->turn_off();
    }
};
void Buzzer::set_frequency(unsigned int new_frequency)
{
    buzzer.period(1 / this->frequency);
    this->frequency = new_frequency;
};
bool Buzzer::is_active()
{
    return this->is_ringing;
};