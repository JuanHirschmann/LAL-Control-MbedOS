#include "drivers/Moisture_sensor.h"
Moisture_sensor::Moisture_sensor(int analog_pin)
{
    this->sensor_pin = analog_pin;
}
void Moisture_sensor::update_reading()
{
    this->reading = analogRead(this->sensor_pin);
}
int Moisture_sensor::get_reading()
{
    this->update_reading();
    return this->reading;
}