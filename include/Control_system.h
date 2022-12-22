#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H
#include "observer_pattern/subjects/Subject.h"
#include "machine_state_pattern/Machine.h"
#include "drivers/Display.h"
#include "user_messages.h"
#include "observer_pattern/observers/System_observer.h"
#include "drivers/Temperature_sensor.h"
#include "drivers/Moisture_sensor.h"
#include "types.h"
#include "drivers/Buzzer.h"
#include "drivers/Motor.h"
#include "drivers/Dual_led.h"
#include "drivers/Digital_dual_led.h"
#include "drivers/Cooler.h"
#include "machine_state_pattern/machine_states/Shutdown_state.h"
class Control_system : public Subject, public Machine
{
    friend class Idle_state;
    friend class Motor_control_state;
    friend class Shutdown_state;
    friend class Check_instruction_state;

public:
    void init();
    void handle_alarm()
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
    void update();
    void wake()
    {
        this->context.shutdown_request = false;
    };
    bool is_off()
    {
        return this->context.shutdown_request;
    }
    void reset_context()
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
    size_t get_cooler_rotation(int cooler)
    {
        if (cooler == 0)
        {
            return this->rear_cooler.get_rotation();
        }
        return this->front_cooler.get_rotation();
    }
    Context_t get_context()
    {
        return this->context;
    }
    bool is_cooler_on(int cooler)
    {
        if (cooler == 0)
        {
            return this->rear_cooler.is_on();
        }
        return this->front_cooler.is_on();
    }
    void display_cooler_speed(float rear_cooler_speed, float front_cooler_speed)
    {
        this->display.set_fan_speed_pct(rear_cooler_speed, front_cooler_speed);
    }
    void set_cooler_speed(float rear_cooler_speed, float front_cooler_speed)
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
    void show_current_step()
    {
        this->display.set_text(PROCEDURE_MESSAGES[this->context.current_step]);
    }
    void show_error_msg()
    {

        this->display.set_text(ERROR_MESSAGES[this->context.current_alarm]);
    }
    void next_step();
    void print(const char *string_out);
    void init_display();
    Control_system(/* args */);
    void notify_observers() override;
    float measure_temperature();
    int measure_moisture();
    void set_next_step_flag(bool new_state);
    bool is_next_step_requested();
    void set_poll_sensors_flag(bool new_state);
    bool is_poll_sensors_requested();
    void set_alarm_flag(bool new_state);
    bool is_alarm_requested();
    void request_alarm(ALARM_TYPES type_of_alarm);
    void request_warning(ALARM_TYPES type_of_warning);
    void set_warning_flag(bool new_state);
    bool is_warning_requested();
    void transition_state();
    ~Control_system();
    bool is_next_step_overriden() { return this->context.override_next_step; };

private:
    Context_t context;

    Display display;

    Temperature_sensor temp_sensor;
    Buzzer buzzer;
    Motor motor;
    Moisture_sensor mois_sensor;
    Dual_LED motor_status_led;
    Digital_dual_LED water_intake_led;
    Digital_dual_LED rear_cooler_led;
    Digital_dual_LED front_cooler_led;
    Cooler front_cooler;
    Cooler rear_cooler;
};

#endif