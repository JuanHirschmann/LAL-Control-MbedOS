/**
 * @file Moisture_sensor.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Implementación de Moisture_sensor.h
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
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