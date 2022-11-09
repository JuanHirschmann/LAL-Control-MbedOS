
#ifndef PC_SERIAL_INTERFACE
#define PC_SERIAL_INTERFACE
#include <mbed.h>
#include "config.h"
#include <string.h>
#include "utils.h"
class PC_serial_interface
{
public:
    PC_serial_interface(PinName tx, PinName rx, unsigned int baud_rate);
    PC_serial_interface(const PC_serial_interface &target_interface);
    ~PC_serial_interface();
    void print(const char *string_out);
    void print(const int int_out);
    void print(const float float_out, int precision);

private:
    unsigned int baud_rate = 0;
    PinName tx_pin;
    PinName rx_pin;
    UnbufferedSerial *uart_interface = nullptr;
};
#endif