/**
 * @file Cooler_observer.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Implementación de Cooler_observer.h
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "observer_pattern/observers/Cooler_observer.h"
#include <stdlib.h>

void Cooler_observer::update(Control_system *subject)
{
    if (subject->is_poll_sensors_requested())
    {
        this->update_speed(subject);
        for (int i = 0; i < MAX_COOLERS; i++)
        {

            if (this->speed[i] == 0 && subject->is_cooler_on(i) == true)
            {
                // ThisThread::sleep_for(100ms);
                this->update_speed(subject);
                if (this->speed[i] == 0 && subject->is_cooler_on(i) == true)
                {
                    subject->request_alarm(HALTED_FAN_ALARM);
                }
            }
        }
    }
};
void Cooler_observer::update_speed(Control_system *subject)
{
    static size_t prev_rotations[2] = {0, 0};
    size_t rotations[MAX_COOLERS];
    rotations[0] = subject->get_cooler_rotation(0);
    rotations[1] = subject->get_cooler_rotation(1);

    this->timer.stop();
    for (int i = 0; i < MAX_COOLERS; i++)
    {
        this->speed[i] = float(rotations[i] - prev_rotations[i]) * 0.5 / (std::chrono::duration<float>(timer.elapsed_time()).count());

        prev_rotations[i] = rotations[i];
    }
    this->timer.reset();
    this->timer.start();
    subject->display_cooler_speed(this->speed[0], speed[1]);
}