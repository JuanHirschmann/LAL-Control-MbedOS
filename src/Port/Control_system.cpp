/**
 * @file Control_system.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Implementación de Control_system.h
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Control_system.h"

Control_system::Control_system(/* args */) : temp_sensor(ONE_WIRE_BUS),
                                             buzzer(BUZZER_PIN, BUZZER_HIGH_FREQ),
                                             motor(MOTOR_CONTROL_PIN),
                                             mois_sensor(MOISTURE_SENSOR_PIN),
                                             front_cooler(FRONT_COOLER_CONTROL_PIN, FRONT_COOLER_SPEED_MEAS_PIN),
                                             rear_cooler(REAR_COOLER_CONTROL_PIN, REAR_COOLER_SPEED_MEAS_PIN),
                                             motor_status_led(MOTOR_GREEN_LED_PIN, MOTOR_RED_LED_PIN),
                                             water_intake_led(WATER_INTAKE_STATE_GREEN_LED, WATER_INTAKE_STATE_RED_LED),
                                             rear_cooler_led(REAR_COOLER_STATE_GREEN_LED, REAR_COOLER_STATE_RED_LED),
                                             front_cooler_led(FRONT_COOLER_STATE_GREEN_LED, FRONT_COOLER_STATE_RED_LED)
{
}
void Control_system::init()
{
    this->current_state = new Shutdown_state();
    this->current_state->enter(this);
    this->reset_context();
};
void Control_system::handle_alarm()
{
    switch (this->context.current_alarm)
    {
    case OVERTEMP_ALARM:
        this->context.shutdown_request = true;
        this->rear_cooler.turn_on(1);
        this->front_cooler.turn_on(1);

        this->motor_status_led.turn_red();
        this->motor.turn_off();
        this->show_error_msg();
        break;

    case HUMIDITY_ALARM:
        this->motor.turn_off();
        this->motor_status_led.turn_red();
        this->context.shutdown_request = true;
        this->rear_cooler.turn_off();
        this->front_cooler.turn_off();
        this->show_error_msg();
        break;
    case HALTED_FAN_ALARM:
        this->motor.turn_off();
        this->motor_status_led.turn_red();
        this->context.shutdown_request = true;
        this->rear_cooler.turn_off();
        this->front_cooler.turn_off();
        this->show_error_msg();
        break;
    case NO_TEMP_SENSOR_ALARM:
        this->motor.turn_off();
        this->motor_status_led.turn_red();
        this->show_error_msg();
        this->context.shutdown_request = true;
        break;
    case OVERTEMP_WARNING:
        this->motor_status_led.turn_yellow();
        this->rear_cooler.turn_on(0.75);
        this->front_cooler.turn_on(0.75);
        break;
    case SLOW_FAN_WARNING:
        break;
    case NO_ALARM:

        this->motor_status_led.turn_green();
        break;
    default:
        this->display.set_text("No se reconoció el error");
        break;
    }
}
void Control_system::update()
{
    this->transition_state();
    this->current_state->update(this);
}
void Control_system::wake()
{
    this->context.shutdown_request = false;
};
bool Control_system::is_off()
{
    return this->context.shutdown_request;
}
void Control_system::reset_context()
{
    this->context.alarm_request = false;
    this->context.warning_request = false;
    this->context.current_step = 0;
    this->context.current_alarm = NO_ALARM;
    this->context.override_next_step = false;
    this->context.shutdown_request = false;
    this->context.warning_request = false;
    this->context.next_step_request = false;

    this->front_cooler.turn_off();
    this->rear_cooler.turn_off();
    this->front_cooler_led.turn_red();
    this->rear_cooler_led.turn_red();
    this->motor_status_led.turn_off();
    this->water_intake_led.turn_red();
}
void Control_system::init_display()
{

    this->display.init();
}
size_t Control_system::get_cooler_rotation(int cooler)
{
    if (cooler == 0)
    {
        return this->rear_cooler.get_rotation();
    }
    return this->front_cooler.get_rotation();
}
Context_t Control_system::get_context()
{
    return this->context;
}
bool Control_system::is_cooler_on(int cooler)
{
    if (cooler == 0)
    {
        return this->rear_cooler.is_on();
    }
    return this->front_cooler.is_on();
}
void Control_system::display_cooler_speed(float rear_cooler_speed, float front_cooler_speed)
{
    this->display.set_fan_speed_pct(rear_cooler_speed, front_cooler_speed);
}
void Control_system::set_cooler_speed(float rear_cooler_speed, float front_cooler_speed)
{
    this->front_cooler.turn_on(front_cooler_speed);
    this->rear_cooler.turn_on(rear_cooler_speed);
    if (rear_cooler_speed == 0)
    {
        this->rear_cooler_led.turn_red();
    }
    else
    {
        this->rear_cooler_led.turn_green();
    }
    if (front_cooler_speed == 0)
    {

        this->front_cooler_led.turn_red();
    }
    else
    {
        this->front_cooler_led.turn_green();
    }
}
void Control_system::show_current_step()
{
    this->display.set_text(PROCEDURE_MESSAGES[this->context.current_step]);
}
void Control_system::show_error_msg()
{

    this->display.set_text(ERROR_MESSAGES[this->context.current_alarm]);
}
void Control_system::next_step()
{
    if (this->context.override_next_step == false)
    {
        this->buzzer.turn_on();
        ThisThread::sleep_for(100ms);
        this->buzzer.turn_off();
        this->context.current_step++;
    }
    if (this->context.current_step < LAST_STEP + 1)
    {

        this->show_current_step();
        this->context.next_step_request = false;
    }
    else
    {
        this->context.shutdown_request = true;
    }
}
void Control_system::notify_observers()
{
    for (int i = 0; i < this->current_observers; i++)
    {
        static_cast<System_observer *>(this->observers[i])->update(this);
    }
    this->set_poll_sensors_flag(false);
};
float Control_system::measure_temperature()
{
    float new_temperature = this->temp_sensor.get_reading();
    this->context.temperature = new_temperature;
    this->display.set_temp(new_temperature);
    return new_temperature;
}
int Control_system::measure_moisture()
{
    return this->mois_sensor.get_reading();
}
void Control_system::set_next_step_flag(bool new_state)
{
    if (!this->is_alarm_requested())
    {

        this->context.next_step_request = new_state;
    }
}
bool Control_system::is_next_step_requested()
{
    return this->context.next_step_request;
}
void Control_system::set_poll_sensors_flag(bool new_state)
{
    this->context.poll_sensors_request = new_state;
}
bool Control_system::is_poll_sensors_requested()
{
    return this->context.poll_sensors_request;
}
void Control_system::set_alarm_flag(bool new_state)
{
    if (this->context.alarm_request != new_state)
    {
        this->context.alarm_request = new_state;
    }
}
bool Control_system::is_alarm_requested()
{
    return this->context.alarm_request;
}
void Control_system::request_alarm(ALARM_TYPES type_of_alarm)
{
    this->context.alarm_request = true;
    this->context.current_alarm = type_of_alarm;
}
void Control_system::request_warning(ALARM_TYPES type_of_warning)
{
    this->context.warning_request = true;
    this->context.current_alarm = type_of_warning;
}
void Control_system::set_warning_flag(bool new_state)
{
    if (this->context.warning_request != new_state)
    {

        this->context.warning_request = new_state;
    }
}
bool Control_system::is_warning_requested()
{
    return this->context.warning_request;
}
void Control_system::transition_state()
{
    Abstract_state *state = this->current_state->transition(this);
    if (state != nullptr)
    {
        delete this->current_state;
        this->current_state = state;
        this->current_state->enter(this);
    }
}
Control_system::~Control_system()
{
    if (this->current_state != nullptr)
    {
        delete this->current_state;
    }
}
