/**
 * @file types.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Archivo de definición de tipos de dato.
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef TYPES_H
#define TYPES_H
/**
 * @brief Enumeración de pasos a realizar del procedimiento
 *
 */
enum STEPS
{
    WELCOME_STEP = 0,
    WATER_ON_STEP = 1,
    OPEN_FAUCET_STEP = 2,
    MOTOR_ON_STEP = 3,
    MOTOR_OFF_STEP = 4,
    MOTOR_COOLDOWN_STEP = 5,
    WATER_OFF_STEP = 6,
    LAST_STEP = 7,
};
/**
 * @brief Tipos de alarmas y advertencias del sistema
 *
 */
enum ALARM_TYPES
{
    NO_ALARM = 0,
    OVERTEMP_ALARM,
    HUMIDITY_ALARM,
    HALTED_FAN_ALARM,
    NO_TEMP_SENSOR_ALARM,
    OVERTEMP_WARNING,
    SLOW_FAN_WARNING,
};
/**
 * @brief Variables de contexto del sistema
 *  @param temperature Última temperatura medida
    @param current_step Paso de procedimiento actual
    @param shutdown_request Booleano con el estado de la solicitud de apagado
    @param warning_request Booleano con el estado de la solicitud de advertencia
    @param alarm_request Booleano con el estado de la solicitud de alarma
    @param next_step_request Booleano con el estado de la solicitud de siguiente paso
    @param poll_sensors_request Booleano con el estado de la solicitud de nueva medicions
    @param override_next_step Booleano para bloquear nuevas solicitudes de siguiente paso
    @param current_alarm Alarma actual
 *
 */
typedef struct
{
    float temperature;
    int current_step;
    bool shutdown_request;
    bool warning_request;
    bool alarm_request;
    bool next_step_request;
    bool poll_sensors_request;
    bool override_next_step;
    ALARM_TYPES current_alarm;

} Context_t;

enum COLOR_TYPES
{
    RED,
    YELLOW,
    GREEN,

};
#endif