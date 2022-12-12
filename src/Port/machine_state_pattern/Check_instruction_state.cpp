#include "machine_state_pattern/machine_states/Check_instruction_state.h"
void Check_instruction_state::update(Control_system *machine)
{
    machine->show_current_step();
    machine->notify_observers();
    machine->display.update();
};
void Check_instruction_state::enter(Control_system *machine)
{
    machine->show_current_step();
    switch (machine->context.current_step)
    {
    case WELCOME_STEP:
        machine->rear_cooler.turn_off();
        machine->front_cooler.turn_off();
        machine->water_intake_led.turn_red();
    case WATER_ON_STEP:
        machine->water_intake_led.turn_green();
    case MOTOR_ON_STEP:
        machine->motor_status_led.turn_green();
        machine->motor.turn_on();
        break;

    case MOTOR_OFF_STEP:
        machine->motor.turn_off();
        break;
    case MOTOR_COOLDOWN_STEP:
        machine->set_cooler_speed(1, 1);
        // machine->context.override_next_step = true;
        /* if (!machine->context.warning_request && !machine->context.alarm_request)
        {
            machine->context.override_next_step = false;
            machine->next_step();
        } */
    default:
        break;
    }
}
Abstract_state *Check_instruction_state::transition(Control_system *machine)
{
    this->exit(machine);
    return new Idle_state();
}