#include "observer_pattern/observers/Cooler_observer.h"
#include <stdlib.h>

#include "PC_serial_interface.h"

PC_serial_interface pc_com(USBTX, USBRX, 9600);
void Cooler_observer::update(Control_system *subject)
{
    this->update_speed(subject);
    for (int i = 0; i < MAX_COOLERS; i++)
    {
        if (this->speed[i] == 0 && subject->is_cooler_on(i) == true)
        {
            subject->request_alarm(HALTED_FAN_ALARM);
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
    pc_com.println((float)this->speed[1]);
    this->timer.reset();
    this->timer.start();
    subject->set_cooler_speed(this->speed[0], speed[1]);
}