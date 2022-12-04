/**
 * @file Moisture_sensor.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Controlador de sensor de humedad analógico.
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MOISTURE_SENSOR_H
#define MOISTURE_SENSOR_H
#include <mbed.h>
/**
 * @brief Clase para el manejo del sensor de humedad analógico.
 *
 */
class Moisture_sensor
{
public:
    /**
     * @brief Construye un nuevo objecto Moisture_sensor
     *
     * @param analog_pin pin analógico donde se conecto el sensor
     */
    Moisture_sensor(PinName analog_pin);
    /**
     * @brief Devuelve la lectura realizada
     *
     * @return int lectura analógica realizada (0 indica conductividad completa, 1023 indica resistividad completa)
     */
    float get_reading();

private:
    /**
     * @brief actualiza el valor de la lectura a realizar.
     *
     */
    void update_reading();
    /**
     * @brief pin analogico donde se conectó el sensor.
     *
     */
    AnalogIn sensor_pin;
    /**
     * @brief lectura realizada.
     *
     */
    float reading = 0.0;
};

#endif