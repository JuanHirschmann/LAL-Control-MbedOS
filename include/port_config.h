/**
 * @file port_config.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Archivo de configuración para los puertos de la placa donde se implementará el sistema.
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef PORT_CONFIG_H
#define PORT_CONFIG_H
const PinName BUTTON_PIN = D2; // D3, tiene que corresponder a una interrupción externa
const PinName MOTOR_CONTROL_PIN = D3;
const int FRONT_COOLER_CONTROL_PIN = D5; // Con PWM
const int REAR_COOLER_CONTROL_PIN = D6;  // Con PWM
const PinName ONE_WIRE_BUS = D7;         // D9 como digital in
const int REAR_COOLER_SPEED_MEAS_PIN = D8;
const int FRONT_COOLER_SPEED_MEAS_PIN = D9;
const PinName MOTOR_GREEN_LED_PIN = D10; // D11, Ambos con PWM
const PinName MOTOR_RED_LED_PIN = D11;   // D10
const PinName BUZZER_PIN = D12;          // D9, necesita PWM

// const int MOISTURE_SENSOR_PIN = A6;

const PinName MOISTURE_SENSOR_PIN = A4; // F401RE no tiene el equivalente a A6
const int FAN_2_STATE_RED_LED = A3;
const int FAN_2_STATE_GREEN_LED = A2;
const int FAN_1_STATE_RED_LED = A1;
const int FAN_1_STATE_GREEN_LED = A0;

#endif