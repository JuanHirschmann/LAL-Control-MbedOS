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

#include "drivers/Cooler.h"
#include "machine_state_pattern/machine_states/Shutdown_state.h"
class Control_system : public Subject, public Machine
{
    friend class Idle_state;
    friend class Motor_control_state;
    friend class Shutdown_state;

public:
    void init();
    void handle_alarm()
    {
        switch (this->context.current_alarm)
        {
        case OVERTEMP_ALARM:
            this->context.shutdown_request = true;
            this->show_error_msg();
            break;

        case HUMIDITY_ALARM:
            this->context.shutdown_request = true;
            this->show_error_msg();
            break;
        case HALTED_FAN_ALARM:
            this->context.shutdown_request = true;
            this->show_error_msg();
            break;
        case NO_TEMP_SENSOR_ALARM:
            this->show_error_msg();
            this->context.shutdown_request = true;
        case OVERTEMP_WARNING:
            break;
        case SLOW_FAN_WARNING:
            break;
        case NO_ALARM:
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
    }
    void count_cooler_rotation()
    {
        if (this->front_cooler.rotation_detected() == HIGH)
        {
            this->front_cooler.count_rotation();
        }
    }
    void show_current_step()
    {
        char buf[MAX_MESSAGE_LENGTH];
        strncpy_P(buf, PROCEDURE_MESSAGES[this->context.current_step], MAX_MESSAGE_LENGTH);
        this->display.set_text(buf);
    }
    void show_error_msg()
    {
        char buf[MAX_MESSAGE_LENGTH];
        strncpy_P(buf, ERROR_MESSAGES[this->context.current_alarm], MAX_MESSAGE_LENGTH);
        this->display.set_text(buf);
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
    // void trigger_buzzer_alarm();
    void request_warning(ALARM_TYPES type_of_warning);
    void set_warning_flag(bool new_state);
    bool is_warning_requested();
    void transition_state();
    Context_t get_context() { return this->context; };
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
    Cooler rear_cooler;
    Cooler front_cooler;
};

#endif