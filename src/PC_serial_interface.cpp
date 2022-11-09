#include "PC_serial_interface.h"

PC_serial_interface::PC_serial_interface(PinName tx, PinName rx, unsigned int baud_rate)
{
    this->tx_pin = tx;
    this->rx_pin = rx;
    this->uart_interface = new UnbufferedSerial(tx, rx, baud_rate);
}
PC_serial_interface::PC_serial_interface(const PC_serial_interface &target_interface)
{
    this->baud_rate = target_interface.baud_rate;
    this->tx_pin = target_interface.tx_pin;
    this->rx_pin = target_interface.rx_pin;
    this->uart_interface = new UnbufferedSerial(target_interface.tx_pin, target_interface.rx_pin, baud_rate);
}
PC_serial_interface::~PC_serial_interface()
{
    delete this->uart_interface;
    this->baud_rate = 0;
}
void PC_serial_interface::print(const char *string_out)
{

    this->uart_interface->write(string_out, strlen(string_out));
}
void PC_serial_interface::print(const int int_out)
{
    char buffer[STRING_BUFFER_SIZE];
    sprintf(buffer, "%d", int_out);
    this->uart_interface->write(buffer, strlen(buffer));
}
void PC_serial_interface::print(const float float_out, int sig_figures)
{
    char buffer[STRING_BUFFER_SIZE];
    ftoa(float_out, buffer, sig_figures);
    this->uart_interface->write(buffer, strlen(buffer));
}