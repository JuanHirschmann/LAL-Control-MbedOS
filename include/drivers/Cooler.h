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
#include "Arduino.h"
#include "system_settings.h"
class Cooler
{
public:
    Cooler(int power_pin, int speed_measurement_pin)
    {
        this->power_pin = power_pin;
        this->speed_measurement_pint = speed_measurement_pin;
        pinMode(power_pin, OUTPUT);
        pinMode(speed_measurement_pin, INPUT_PULLUP);
    }
    void turn_on(float duty_cycle = 1.0)
    {
        if (duty_cycle < FAN_MINIMUM_DUTY_CYCLE) //
        {
            Serial.println("Te apague");
            this->turn_off();
        }
        else
        {
            if (!this->is_on && duty_cycle < FAN_AUTONOMOUS_DUTY_CYCLE)
            {

                Serial.println("Te ayudé");
                this->turn_on(1.0); // Necesita inercia
                delay(DEFAULT_DELAY);
            }
            this->is_on = true;
            this->current_duty_cycle = duty_cycle;
            analogWrite(this->power_pin, int(MAX_ANALOG_WRITE_VALUE * this->current_duty_cycle));
        }
    }
    void turn_off()
    {
        this->is_on = false;
        analogWrite(this->power_pin, 0);
    }
    float get_speed()
    {
        return this->current_RPS;
    }
    bool rotation_detected()
    {
        return digitalRead(this->speed_measurement_pint);
    }
    void count_rotation()
    {
        unsigned long current_millis_call = millis();
        static unsigned long prev_millis_call = current_millis_call;
        this->rotations_in_sample_period++;
        if (prev_millis_call != 0 && current_millis_call - prev_millis_call > FAN_SPEED_SAMPLE_PERIOD)
        {
            unsigned int time_diff = current_millis_call - prev_millis_call;
            prev_millis_call = current_millis_call;
            this->rotations_in_sample_period /= 2;                                   // 2 estados altos por rotación.
            this->current_RPS = float(this->rotations_in_sample_period) / time_diff; // 6000/2
            this->rotations_in_sample_period = 0;
        }
    }

private:
    bool is_on = false;
    unsigned long int rotations_in_sample_period = 0;
    int power_pin;
    int speed_measurement_pint;
    float current_duty_cycle = 0;
    float current_RPS = 0;
};