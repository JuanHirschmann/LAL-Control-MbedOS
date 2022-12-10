
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
/* void poll_sensors()
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

  Temperature_sensor temp_sensor(ONE_WIRE_BUS);
  Dual_LED led(MOTOR_GREEN_LED_PIN, MOTOR_RED_LED_PIN);
  Moisture_sensor mois_sensor(MOISTURE_SENSOR_PIN);
  Motor motor(MOTOR_CONTROL_PIN);
  motor.turn_on();
  Buzzer buzzer(BUZZER_PIN, 1);
  led.turn_red();
  // buzzer.turn_on();
  while (true)
  {
    //led.toggle();
    ThisThread::sleep_for(1000ms);
  }
}; */
/* // SPI Communication

// TextLCD lcd(p15, p16, p17, p18, p19, p20);                // RS, E, D4-D7, LCDType=LCD16x2, BL=NC, E2=NC, LCDTCtrl=HD44780
// TextLCD_SPI lcd(&spi_lcd, p8, TextLCD::LCD40x4);   // SPI bus, 74595 expander, CS pin, LCD Type
// TextLCD_I2C lcd(&i2c_lcd, 0x42, TextLCD::LCD16x2, TextLCD::WS0010); // I2C bus, PCF8574 Slaveaddress, LCD Type, Device Type
// TextLCD_SPI_N lcd(&spi_lcd, p8, p9);               // SPI bus, CS pin, RS pin, LCDType=LCD16x2, BL=NC, LCDTCtrl=ST7032_3V3
// TextLCD_I2C_N lcd(&i2c_lcd, ST7032_SA, TextLCD::LCD16x2, NC, TextLCD::ST7032_3V3); // I2C bus, Slaveaddress, LCD Type, BL=NC, LCDTCtrl=ST7032_3V3

I2C i2c_lcd(D14, D15); // SDA, SCL
// I2C i2c_lcd(p28,p27); // SDA, SCL

// SPI Communication
// SPI spi_lcd(p5, NC, p7); // MOSI, MISO, SCLK

// LCD instantiation
// TextLCD lcd(p15, p16, p17, p18, p19, p20, TextLCD::LCD20x2);        // 4bit bus: rs, e, d4-d7
TextLCD_I2C lcd(&i2c_lcd, 0x4E, TextLCD::LCD20x4); // I2C exp: I2C bus, PCF8574 Slaveaddress, LCD Type
// TextLCD_I2C lcd(&i2c_lcd, 0x42, TextLCD::LCD16x2, TextLCD::WS0010); // I2C exp: I2C bus, PCF8574 Slaveaddress, LCD Type, Ctrl Type
// TextLCD_I2C lcd(&spi_lcd, p8, TextLCD::LCD24x4D);                   // I2C exp: SPI bus, CS pin, LCD Type
// TextLCD_SPI_N lcd(&spi_lcd, p8, p9, TextLCD::LCD16x2, NC, TextLCD::ST7032_3V3); // SPI native: SPI bus, CS pin, RS pin, LCDType=LCD16x2, BL=NC, LCDTCtrl=ST7032
// TextLCD_I2C_N lcd(&i2c_lcd, ST7032_SA, TextLCD::LCD16x2, NC, TextLCD::ST7032_3V3); // I2C native: I2C bus, slaveaddress, LCDType=LCD16x2, BL=NC, LCDTCtrl=ST7032 =Ok
// TextLCD_I2C_N lcd(&i2c_lcd, SSD1803_SA1, TextLCD::LCD20x4D, NC, TextLCD::SSD1803_3V3); // I2C native: I2C bus, slaveaddress, LCDType=LCD20x4D, BL=NC, LCDTCtrl=SSD1803 =Ok

int main()
{
  Timer t;
  for (int row = 0; row < lcd.rows(); row++)
  {
    int col = 0;

    lcd.putc('0' + row);

    for (col = 1; col < lcd.columns() - 1; col++)
    {
      lcd.putc('*');
    }

    lcd.putc('+');
  }

  // Fill screen again and time it
  t.start();

  for (int row = 0; row < lcd.rows(); row++)
  {
    int col = 0;

    lcd.putc('0' + row);

    for (col = 1; col < lcd.columns() - 1; col++)
    {
      lcd.putc('*');
    }

    lcd.putc('+');
  }
  t.stop();

  // Show cursor as blinking character
  lcd.setCursor(TextLCD::CurOff_BlkOn);

  // Set and show user defined characters. A maximum of 8 UDCs are supported by the HD44780.
  // They are defined by a 5x7 bitpattern.

} */
/*  I2C i2c(I2C_SDA, I2C_SCL);

int main()
{
  ThisThread::sleep_for(1000ms);
  printf("\nI2C Scanner running...\n");
  // i2c.frequency(400000);
  int error, address, nDevices;
  nDevices = 0;
  for (address = 0; address < 128; address++)
  {
    thread_sleep_for(10);
    error = i2c.write(address << 1, "1", 1);

    if (error == 0)
    {
      printf("I2C device found at address 8bit: 0x%X 7bit: 0x%X\n", address, address << 1);
      nDevices++;
    }
  }
  if (nDevices == 0)
  {
    printf("No I2C devices found\n");
  }
  else
  {
    printf("\ndone\n");
  }
} */
int main()
{
  hd44780_I2Cexp lcd(D14, D15);
  lcd.begin();
  lcd.cursor(0, 0);
  lcd.enable_line_wrap();
  while (true)
  {
    lcd.home();
    lcd.print("Hola juan como estas ya comiste");

    ThisThread::sleep_for(1000ms);
    lcd.clear();
    ThisThread::sleep_for(1000ms);
  }
}