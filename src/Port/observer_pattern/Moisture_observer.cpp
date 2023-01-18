/**
 * @file Moisture_observer.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Implementación de Moisture_observer.h
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "observer_pattern/observers/Moisture_observer.h"
void Moisture_observer::update(Control_system *subject)
{
    if (subject->is_poll_sensors_requested())
    {
        int moisture = subject->measure_moisture();

        if (moisture < MOISTURE_ALARM_THRESHOLD)
        {

            subject->request_alarm(HUMIDITY_ALARM);
        }
    }
};