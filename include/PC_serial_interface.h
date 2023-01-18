
/**
 * @brief Clase para el manejo de la interfaz serie para comunicarse con una PC
 * (Sólo utilizado para pruebas)
 *
 */
#ifndef PC_SERIAL_INTERFACE
#define PC_SERIAL_INTERFACE
#include <mbed.h>
#include <string.h>
#include "utils.h"
const int STRING_BUFFER_SIZE = 60;

class PC_serial_interface
{
public:
    /**
     * @brief Construye un nuevo objecto pc serial interface
     *
     * @param tx Pin de transmisión
     * @param rx Pin de recepción
     * @param baud_rate Velocidad de interfaz [Baudios]
     */
    PC_serial_interface(PinName tx, PinName rx, unsigned int baud_rate);
    /**
     * @brief Construye un nuevo objecto pc serial interface
     *
     * @param target_interface objeto tipo PC_serial_interface a copiar.
     */
    PC_serial_interface(const PC_serial_interface &target_interface);
    /**
     * @brief Destruye el objecto pc serial interface
     *
     */
    ~PC_serial_interface();
    /**
     * @brief Imprime en la interfaz serie
     *
     * @param string_out Cadena de texto a imprimir
     */
    void print(const char *string_out);
    /**
     * @brief Imprime en la interfaz serie
     *
     * @param int_out número entero a imprimir
     */
    void print(const int int_out);
    /**
     * @brief Imprime en la interfaz serie
     *
     * @param float_out número flotante a imprimir
     * @param sig_figures decimales despues de la coma
     */
    void println(const float float_out, int sig_figures = 1);
    /**
     * @brief Imprime en la interfaz serie con salto de línea.
     *
     * @param string_out Cadena de texto a imprimir
     */
    void println(const char *string_out);
    /**
     * @brief Imprime en la interfaz serie con salto de línea.
     *
     * @param int_out número entero a imprimir
     */
    void println(const int int_out);
    /**
     * @brief Imprime en la interfaz serie con salto de línea.
     *
     * @param float_out número flotante a imprimir
     * @param sig_figures decimales despues de la coma
     */
    void print(const float float_out, int sig_figures = 1);
    /**
     * @brief Lee una cadena de texto de la interfaz serie
     *
     * @param string cadena de texto donde almacenar lo leido
     * @param length Largo de la cadena a leer.
     */
    void read(char *string, int length);
    /**
     * @brief repite caracter a caracter lo leido de la interfaz serie.
     *
     */
    void echo();

private:
    unsigned int baud_rate = 0;
    PinName tx_pin;
    PinName rx_pin;
    UnbufferedSerial *uart_interface = nullptr;
};
#endif