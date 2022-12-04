#include "drivers/Moisture_sensor.h"
Moisture_sensor::Moisture_sensor(PinName analog_pin) : sensor_pin(analog_pin)
{
}
void Moisture_sensor::update_reading()
{
    this->reading = sensor_pin.read();
}
float Moisture_sensor::get_reading()
{
    this->update_reading();
    return this->reading;
}