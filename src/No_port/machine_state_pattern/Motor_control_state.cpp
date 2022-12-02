#include "machine_state_pattern/machine_states/Motor_control_state.h"
#include "Arduino.h"
void Motor_control_state::enter(Control_system *machine)
{
    Serial.println(F("Estado motor control"));
    machine->motor_status_led.turn_red();
}
void Motor_control_state::update(Control_system *machine)
{

    if (!machine->context.alarm_request)
    {
        machine->buzzer.turn_off();
        if (machine->context.warning_request)
        {

            machine->motor_status_led.turn_yellow();
        }
        else
        {
            machine->motor_status_led.turn_green();
        }
        machine->show_current_step();
    }
    else
    {
        machine->buzzer.toggle();
        machine->motor_status_led.turn_red();
        machine->motor.turn_off();
        machine->context.override_next_step = true;
        machine->handle_alarm();
    }

    switch (machine->context.current_step)
    {
    case MOTOR_ON_STEP:
        machine->motor.turn_on();
        break;

    case MOTOR_OFF_STEP:
        machine->motor.turn_off();
        break;
    case MOTOR_COOLDOWN_STEP:
        machine->context.override_next_step = true;
        if (!machine->context.warning_request && !machine->context.alarm_request)
        {
            machine->context.override_next_step = false;
            machine->next_step();
        }
    default:
        break;
    }

    machine->notify_observers();
    machine->display.update();
}
void Motor_control_state::exit(Control_system *machine)
{
    machine->motor_status_led.turn_off();
    machine->buzzer.turn_off();
}
Abstract_state *Motor_control_state::transition(Control_system *machine)
{

    if ((machine->context.current_step < MOTOR_ON_STEP || machine->context.current_step > MOTOR_COOLDOWN_STEP) && !(machine->context.warning_request || machine->context.alarm_request))
    {
        this->exit(machine);
        return new Idle_state();
    }
    else if (machine->context.shutdown_request)
    {
        unsigned long current_millis_call = millis();
        static unsigned long prev_millis_call = current_millis_call;
        if (prev_millis_call != 0 && current_millis_call - prev_millis_call > 5000)
        {
            prev_millis_call = current_millis_call;
            this->exit(machine);
            return new Shutdown_state();
        }
    }
    return nullptr;
}
