/**
 * @file Display.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Implementación de Display.h
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "drivers/Display.h"
#include "port_config.h"
#include "PC_serial_interface.h"

Display::Display() : screen_interface(SDA, SCL)
{
    // No inicializar objecto de interfaz de pantalla en el constructor.
}
void Display::init()
{

    this->screen_interface.begin();
    this->screen_interface.lineWrap();
    this->screen_interface.home();
}
void Display::set_temp(float new_temp)
{
    if (this->on_screen_temp != new_temp)
    {

        this->on_screen_temp = new_temp;
        this->update_needed = true;
    }
}
void Display::set_fan_speed_pct(float back_speed_pct, float front_speed_pct)
{

    float cooler_speed_variation = 1;
    if (back_speed_pct != 0)
    {
        cooler_speed_variation = abs(this->on_screen_fan_speed_pct[0] - back_speed_pct) / back_speed_pct;
    }
    else if (this->on_screen_fan_speed_pct[0] == 0)
    {
        cooler_speed_variation = 0;
    }
    if (cooler_speed_variation > 0.1)
    {
        this->on_screen_fan_speed_pct[0] = back_speed_pct;
        this->update_needed = true;
    }
    if (front_speed_pct != 0)
    {
        cooler_speed_variation = abs(this->on_screen_fan_speed_pct[1] - front_speed_pct) / front_speed_pct;
    }
    else if (this->on_screen_fan_speed_pct[1] == 0)
    {
        cooler_speed_variation = 0;
    }
    if (cooler_speed_variation > 0.1)
    {
        this->on_screen_fan_speed_pct[1] = front_speed_pct;
        this->update_needed = true;
    }
}
void Display::set_text(const char *string_out)
{

    if (strncmp(string_out, this->on_screen_text, MAX_DISPLAY_STRING_LENGTH) != 0)
    {
        strncpy(this->on_screen_text, string_out, MAX_DISPLAY_STRING_LENGTH);
        this->update_needed = true;
    }
}
void Display::update()
{
    if (this->update_needed)
    {
        this->screen_interface.clear();
        this->screen_interface.home();

        this->screen_interface.print(this->on_screen_text);
        this->screen_interface.cursor(TEMP_INDICATOR_CURSOR_OFFSET[0], TEMP_INDICATOR_CURSOR_OFFSET[1]);
        this->screen_interface.print(this->on_screen_temp, 1);
        this->screen_interface.cursor(FAN_INDICATOR_CURSOR_OFFSET[0], FAN_INDICATOR_CURSOR_OFFSET[1]);
        this->screen_interface.print(this->on_screen_fan_speed_pct[0], 1);
        this->screen_interface.cursor(FAN_INDICATOR_CURSOR_OFFSET[0] + 7, FAN_INDICATOR_CURSOR_OFFSET[1]);

        this->screen_interface.print(this->on_screen_fan_speed_pct[1], 1);

        this->update_needed = false;
    }
}
void Display::turn_off()
{
    this->screen_interface.turn_off();
}
void Display::turn_on()
{
    this->screen_interface.turn_on();
}