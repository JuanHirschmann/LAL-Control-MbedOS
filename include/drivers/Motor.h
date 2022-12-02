/**
 * @file Motor.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Controlador de motor de 220 VAC
 * @version 0.1
 * @date 2022-11-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"
#include "port_config.h"

class Motor
/**
 * @brief Clase para el manejo del motor salida digital.
 *
 */
{
public:
    /**
     * @brief Construye un nuevo objecto Motor
     *
     * @param motor_pin Pin elegido para conectar el motor, sólo sálida digital.
     */
    Motor(int motor_pin);
    /**
     * @brief Enciende el motor con con una duración en milisegundos duration,
     *  por defecto enciende el motor por un tiempo indefinido.
     *
     */
    void turn_on();
    /**
     * @brief Apaga el motor.
     *
     */
    void turn_off();
    /**
     * @brief Devuelve el estado del motor
     *
     * @return true El motor está activo.
     * @return false El motor está inactivo.
     */
    bool is_active();

private:
    bool is_on = false;
    int motor_pin;
};
#endif