/**
 * @file Moisture_observer.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Observador del sensor de temperatura
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MOISTURE_OBSERVER_H
#define MOISTURE_OBSERVER_H
#include "observer_pattern/observers/System_observer.h"
#include "Arduino.h"
#include "Control_system.h"
#include "system_settings.h"
#include "types.h"
/**
 * @brief Clase heredera de System_observer, creada para observar
 *  el estado de los sensores de humedad.
 *
 */
class Moisture_observer : public System_observer
{
public:
    /**
     * @brief Actualización del observador, mide la humedad y, si excede el umbral
     * MOISTURE_ALARM_THRESHOLD, solicita una alarma del tipo HUMIDITY_ALARM.
     *
     * @param subject sujeto a observar
     */
    void update(Control_system *subject);

private:
};
#endif