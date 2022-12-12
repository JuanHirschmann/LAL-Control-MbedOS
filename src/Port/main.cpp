
#include "main.h"

Control_system control;
Instruction_observer inst_obs;
Temperature_observer temp_obs;
Moisture_observer mois_obs;
Cooler_observer cooler_obs;

void poll_sensors()
{
  control.set_poll_sensors_flag(true);
}
void button_pressed()
{
  if (control.is_off())
  {
    control.wake();
  }
  else
  {
    control.set_next_step_flag(true);
  }
}

int main()
{

  control.init();
  control.attach(&inst_obs);
  control.attach(&temp_obs);
  control.attach(&mois_obs);
  control.attach(&cooler_obs);
  DebounceIn button(BUTTON_PIN);
  Ticker sensor_poller;
  button.rise(callback(button_pressed));
  sensor_poller.attach(&poll_sensors, 1000ms);

  while (true)
  {
    control.update();
  }
}