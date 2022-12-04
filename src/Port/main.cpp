
#include "main.h"

/* Control_system control;
Instruction_observer inst_obs;
Temperature_observer temp_obs;
Moisture_observer mois_obs; */

/*
ISR(PCINT0_vect)
{
    control.count_cooler_rotation();
} */
/* void count_rotation()
{
  cli();
  Serial.print("ACA");
  // cooler.count_rotation();
  sei();
} */
/* void setup()
{
  // cli();
  // Serial.begin(9600);
  // pinMode(ONE_WIRE_BUS, INPUT);
  // setup_timer1_interrupt();
  // setup_int0_interrupt(BUTTON_PIN, INPUT_PULLUP, int0_callback, HIGH);
  // setup_pinct_portb_interrupt();
   control.init();
  control.attach(&inst_obs);
  control.attach(&temp_obs);
  control.attach(&mois_obs);
//   sei();
}*/

PC_serial_interface pc_com(USBTX, USBRX, 9600);
void poll_sensors()
{
  // control.set_poll_sensors_flag(true);
  pc_com.print("POLL");
}

void button_pressed()
{
  pc_com.println("apreté");
}
int main()
{
  // control.update();
  //  delay(1000);
  DebounceIn button(BUTTON_PIN);
  Ticker sensor_poller;
  button.rise(callback(button_pressed));
  sensor_poller.attach(&poll_sensors, 1.0);
  Buzzer buzzer(BUZZER_PIN, 4000);
  Temperature_sensor temp_sensor(ONE_WIRE_BUS);
  Dual_LED led(MOTOR_GREEN_LED_PIN, MOTOR_RED_LED_PIN);
  Moisture_sensor mois_sensor(MOISTURE_SENSOR_PIN);
  Motor motor(MOTOR_CONTROL_PIN);
  led.turn_on();

  while (true)
  {
  }
};