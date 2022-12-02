/**
 * @file Temperature_observer.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Observador del sensor de temperatura.
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef TEMPERATURE_OBSERVER_H
#define TEMPERATURE_OBSERVER_H
#include "observer_pattern/observers/System_observer.h"
#include "Arduino.h"
#include "Control_system.h"
#include "system_settings.h"
#include "types.h"
/**
 * @brief Clase heredera de System_observer, creada para observar
 *  el estado de los sensores de temperatura.
 *
 */
class Temperature_observer : public System_observer
{
public:
    /**
     * @brief Actualización del observador, mide la temperatura:
     * si excede el umbral OVERTEMP_ALARM_TRESHOLD, solicita una alarma del tipo OVERTEMP_ALARM.
     * si excede el umbral OVERTEMP_WARNING_TRESHOLD, solicita una advertencia del tipo OVERTEMP_WARNING.
     * Para desactivar las alarmas, la temperatura debe HYSTERESIS_PERCENT veces menor del umbral que le corresponde.
     * @param subject sujeto a observar
     */
    void update(Control_system *subject);

private:
};
#endif