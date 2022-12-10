#include "drivers/Cooler.h"
#include <functional>

Cooler::Cooler(PinName power_pin, PinName speed_measurement_pin) : power_pin(power_pin), speed_measurement_pin(speed_measurement_pin)
{
    this->speed_measurement_pin.mode(PullUp);
    this->speed_measurement_pin.rise(callback(this, &Cooler::count_rotation));
}
void Cooler::turn_on(float duty_cycle)
{
    if (duty_cycle < FAN_MINIMUM_DUTY_CYCLE) //
    {
        this->turn_off();
    }
    else
    {
        if (!this->_is_on && duty_cycle < FAN_AUTONOMOUS_DUTY_CYCLE)
        {

            this->turn_on(1.0); // Necesita inercia
            // delay(DEFAULT_DELAY);
            // ThisThread::sleep_for(DEFAULT_DELAY);
            ThisThread::sleep_for(100ms);
        }
        this->_is_on = true;
        this->current_duty_cycle = duty_cycle;
        this->power_pin.write(duty_cycle);
    }
}
void Cooler::turn_off()
{
    this->_is_on = false;
    this->power_pin.write(0);
}
void Cooler::count_rotation()
{
    if (this->rotations_in_sample_period != (size_t)-1)
    {

        this->rotations_in_sample_period++;
    }
    else
    {
        this->rotations_in_sample_period = 0;
    }
}
size_t Cooler::get_rotation()
{
    return this->rotations_in_sample_period;
}