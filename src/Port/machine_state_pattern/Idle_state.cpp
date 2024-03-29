/**
 * @file Idle_state.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Implementación de Idle_state.h
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "machine_state_pattern/machine_states/Idle_state.h"
void Idle_state::enter(Control_system *machine)
{
    machine->show_current_step();
}
void Idle_state::update(Control_system *machine)
{
    machine->show_current_step();
    machine->notify_observers();
    machine->display.update();
}
void Idle_state::exit(Control_system *machine)
{
    // machine->buzzer.turn_off();
    //  machine->motor_status_led.turn_off();
}
Abstract_state *Idle_state::transition(Control_system *machine)
{
    if (machine->context.warning_request || machine->context.alarm_request)
    {

        this->exit(machine);
        return new Alarm_state();
    }
    else if (machine->context.next_step_request)
    {
        this->exit(machine);
        return new Check_instruction_state();
    }
    return nullptr;
}
/* else if (machine->context.shutdown_request)
   {
       this->exit(machine);
       return new Shutdown_state();
   } */