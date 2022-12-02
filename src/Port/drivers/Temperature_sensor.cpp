/**
 * @file Temperature_sensor.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "drivers/Temperature_sensor.h"
// Uso -127 para avisar error
Temperature_sensor::Temperature_sensor(PinName one_wire_bus) : DS18B20_sensor(one_wire_bus)
{
  this->init_sensors();
}
float Temperature_sensor::get_reading()
{

  return this->reading;
}
void Temperature_sensor::update_readings()
{
  this->available_ds18_devices = 1;
  this->DS18B20_sensor.startConversion();
  ThisThread::sleep_for(350ms);
  for (int i = 0; i < this->available_ds18_devices; i++)
  {
    this->reading = this->DS18B20_sensor.read();
  }
}
void Temperature_sensor::init_sensors()
{
  this->DS18B20_sensor.begin();
  this->available_ds18_devices = 1;
}
