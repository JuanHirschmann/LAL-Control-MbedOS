#include "machine_state_pattern/machine_states/Check_instruction_state.h"
#include "PC_serial_interface.h"
PC_serial_interface pc_com(USBTX, USBRX, 9600);
void Check_instruction_state::exit(Control_system *machine){
    // machine->context.override_next_step = false;
};
void Check_instruction_state::update(Control_system *machine)
{
    if (machine->context.shutdown_request)
    {
        machine->reset_context();
    }

    machine->notify_observers();
    machine->display.update();
};
void Check_instruction_state::enter(Control_system *machine)
{
    // machine->context.override_next_step = true;
    switch (machine->context.current_step)
    {
    case WELCOME_STEP:
        machine->rear_cooler.turn_off();
        machine->front_cooler.turn_off();
        machine->water_intake_led.turn_red();
        pc_com.println("Bienvenida");
        break;
    case WATER_ON_STEP:

        machine->water_intake_led.turn_green();

        pc_com.println("agua");
        break;
    case MOTOR_ON_STEP:
        if (!machine->context.warning_request)
        {
            machine->motor_status_led.turn_green();
            machine->set_cooler_speed(0.25, 0.25);
        }
        if (!machine->context.alarm_request)
        {
            machine->motor.turn_on();
        }
        pc_com.println("motor");
        break;

    case MOTOR_OFF_STEP:
        if (!machine->context.warning_request)
        {
            machine->set_cooler_speed(0.5, 0.5);
        }
        machine->motor.turn_off();
        pc_com.println("motor off");
        break;
    case MOTOR_COOLDOWN_STEP:
        machine->context.override_next_step = true;
        if (!machine->context.warning_request)
        {
            machine->context.override_next_step = false;
        }

        pc_com.println("cooldown");
        break;
    case WATER_OFF_STEP:
        machine->set_cooler_speed(0, 0);
        machine->water_intake_led.turn_red();
    default:
        break;
    }
    machine->next_step();
}
Abstract_state *Check_instruction_state::transition(Control_system *machine)
{
    if (!machine->is_next_step_requested())
    {

        this->exit(machine);

        return new Idle_state();
    }
    return nullptr;
}