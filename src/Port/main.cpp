
#include "main.h"
/* Control_system control;
Instruction_observer inst_obs;
Temperature_observer temp_obs;
Moisture_observer mois_obs; */

/* void int0_callback()
{
    cli();
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();

    if (interrupt_time - last_interrupt_time > DEBOUNCE_CONSTANT)
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
    last_interrupt_time = interrupt_time;

    sei();
}
ISR(TIMER1_COMPA_vect)
{
    cli();
    control.set_poll_sensors_flag(true);
    sei();
}
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
  /* control.init();
  control.attach(&inst_obs);
  control.attach(&temp_obs);
  control.attach(&mois_obs);
//   sei();
}*/

/* int main()
{
  PwmOut led(D9);
  led.period(0.001);
  while (1)
  {
    led = led + 0.01;
    ThisThread::sleep_for(200);
    if (led == 1.0)
    {
      led = 0;
    }
  }
} */

int main()
{
  // control.update();
  //  delay(1000);
  Buzzer buzzer(BUZZER_PIN, 4000);
  Temperature_sensor temp_sensor(ONE_WIRE_BUS);
  PC_serial_interface pc_com(USBTX, USBRX, 9600);

  while (true)
  {
    ThisThread::sleep_for(1s);
    pc_com.print(temp_sensor.get_reading(), 3);
    pc_com.print("\n");
  }
};