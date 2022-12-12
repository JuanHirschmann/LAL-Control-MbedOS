/**
 * @file user_messages.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Archivo para la configuración de interfaz con el usuario.
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef USER_MESSAGES_H
#define USER_MESSAGES_H
const int MAX_MESSAGE_LENGTH = 70;
const int MAX_PROCEDURE_STEPS = 8;
const int ERROR_TYPES = 5;
static const char PROCEDURE_MESSAGES[MAX_PROCEDURE_STEPS][MAX_MESSAGE_LENGTH] = {
    {"LAL: Sistema de control de procedimiento.\0"},
    {"Confirmar funcionamiento de canilla de agua.\0"},
    {"Abrir conexión de vacio y extracción.\0"},
    {"Encender extractor.\0"},
    {"Apagar extractor.\0"},
    {"Motor apagado.Esperando a que baje la temperatura.\0"},
    {"Cierre la llave de agua\0"},
    {"CONFIRMAR APAGADO\0"},
};
/*enum ALARM_TYPES
{
    NO_ALARM=0,
    OVERTEMP_ALARM,
    HUMIDITY_ALARM,
    HALTED_FAN_ALARM,
    NO_TEMP_SENSOR_ALARM,
    OVERTEMP_WARNING,
    SLOW_FAN_WARNING,
}; DEFINIR ERROR_MESSAGES EN EL ORDEN DE LOS ALARM TYPES*/
static const char ERROR_MESSAGES[ERROR_TYPES][MAX_MESSAGE_LENGTH] = {
    {"No hay alarma\0"},
    {"Exceso de temperatura.\0"},
    {"Humedad en motor.\0"},
    {"Ventilador no detectado.\0"},
    {"Sensor de temperatura no detectado.\0"},
};
#endif