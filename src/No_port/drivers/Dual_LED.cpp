#include "drivers/Dual_LED.h"
Dual_LED::Dual_LED(int green_led_pin, int red_led_pin)
{
    this->green_led_pin = green_led_pin;
    this->red_led_pin = red_led_pin;
    pinMode(green_led_pin, OUTPUT);
    pinMode(green_led_pin, OUTPUT);
};
void Dual_LED::set_color(COLOR_TYPES new_color)
{
    this->current_color = new_color;
    switch (new_color)
    {
    case GREEN:
        this->green_led_duty_cycle = GREEN_COLOR_DUTY_CYCLE[0];
        this->red_led_duty_cycle = GREEN_COLOR_DUTY_CYCLE[1];
        break;

    case YELLOW:
        this->green_led_duty_cycle = YELLOW_COLOR_DUTY_CYCLE[0];
        this->red_led_duty_cycle = YELLOW_COLOR_DUTY_CYCLE[1];
        break;

    case RED:
        this->green_led_duty_cycle = RED_COLOR_DUTY_CYCLE[0];
        this->red_led_duty_cycle = RED_COLOR_DUTY_CYCLE[1];
        break;

    default:
        break;
    }
}

void Dual_LED::turn_red()
{
    this->set_color(RED);
    this->turn_on();
}
void Dual_LED::turn_green()
{
    this->set_color(GREEN);
    this->turn_on();
}
void Dual_LED::turn_yellow()
{
    this->set_color(YELLOW);
    this->turn_on();
}
void Dual_LED::turn_on()
{
    this->is_on = true;
    int value = (this->green_led_duty_cycle * MAX_ANALOG_WRITE_VALUE);
    analogWrite(this->green_led_pin, value);
    value = int(this->red_led_duty_cycle * MAX_ANALOG_WRITE_VALUE);
    analogWrite(this->red_led_pin, value);
}
void Dual_LED::toggle()
{
    if (this->is_on)
    {
        this->turn_off();
    }
    else
    {
        this->turn_on();
    }
}
void Dual_LED::turn_off()
{
    this->is_on = false;
    analogWrite(this->green_led_pin, 0);
    analogWrite(this->red_led_pin, 0);
    // digitalWrite(this->green_led_pin, LOW);
    // digitalWrite(this->red_led_pin, LOW);
}