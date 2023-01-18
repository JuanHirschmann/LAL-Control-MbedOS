/**
 * @file hd44780_I2Cexp.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Adaptación de la biblioteca TextLCD de MbedOS 5. Permite utilizar un LCD hd44780 con un expansor de puerto mediante I2C.
 * @version 0.1
 * @date 2023-01-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _HD44780_I2CEXP_H
#define _HD44780_I2CEXP_H
#include <mbed.h>
#include <stdlib.h>
#include "hd44780_instruction_set.h"
#include "utils.h"
#include "display_settings.h"
/**
 * @brief Tipo de dato para las coordenadas del cursor.
 *
 */
typedef struct
{
    int x_pos;
    int y_pos;
} coordinates_t;
/**
 * @brief Tipo de dato para el manejo del integrafo PCF8574
 *
 */
typedef struct
{
    int address;
    char data;
    bool displayPinRs;
    bool displayPinRw;
    bool displayPinEn;
    bool displayPinA;
    bool displayPinD4;
    bool displayPinD5;
    bool displayPinD6;
    bool displayPinD7;
} pcf8574_t;
class hd44780_I2Cexp
{

public:
    /**
     * @brief Habilita la envoltura de líneas automática. Cualquier oración que sea demasiado larga como
     * para mostrarse en una única línea será recortada y continuada en la fila directamente inferior.
     *
     */
    void lineWrap()
    {
        this->line_wrap = true;
    }
    /**
     * @brief Lleva el cursor al origen de coordenadas
     *
     */
    void home()
    {
        cursor_position.x_pos = 0;
        cursor_position.y_pos = 0;
        this->cursor(0, 0);
    }
    /**
     * @brief Borra el texto de la pantalla
     *
     */
    void clear()
    {
        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_CLEAR_DISPLAY);
    };
    /**
     * @brief Activa la retroiluminación
     *
     */
    void turn_on()
    {
        this->clear();
        this->send_command(DISPLAY_RS_INSTRUCTION, DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_ON);
    }
    /**
     * @brief Desactiva la retroiluminación
     *
     */
    void turn_off()
    {
        this->clear();
        this->send_command(DISPLAY_RS_INSTRUCTION, DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_OFF);
    }
    /**
     * @brief Ejecuta la secuencia de inicialización del display.
     *
     */
    void begin()
    {

        this->pcf8574_data.address = PCF8574_I2C_BUS_8BIT_WRITE_ADDRESS;
        this->pcf8574_data.data = 0b00000000;
        this->pcf8574_i2c.frequency(100000);
        this->pin_write(DISPLAY_PIN_A_PCF8574, 1);

        this->is_initial_8bit_complete = false;
        ThisThread::sleep_for(50ms);

        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_FUNCTION_SET |
                               DISPLAY_IR_FUNCTION_SET_8BITS);
        ThisThread::sleep_for(5ms);

        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_FUNCTION_SET |
                               DISPLAY_IR_FUNCTION_SET_8BITS);
        ThisThread::sleep_for(1ms);

        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_FUNCTION_SET |
                               DISPLAY_IR_FUNCTION_SET_8BITS);
        ThisThread::sleep_for(1ms);

        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_FUNCTION_SET |
                               DISPLAY_IR_FUNCTION_SET_4BITS);
        ThisThread::sleep_for(1ms);

        this->is_initial_8bit_complete = true;

        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_FUNCTION_SET |
                               DISPLAY_IR_FUNCTION_SET_4BITS |
                               DISPLAY_IR_FUNCTION_SET_2LINES |
                               DISPLAY_IR_FUNCTION_SET_5x8DOTS);
        ThisThread::sleep_for(1ms);

        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_DISPLAY_CONTROL |
                               DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_OFF |
                               DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF |
                               DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF);
        ThisThread::sleep_for(1ms);

        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_CLEAR_DISPLAY);
        ThisThread::sleep_for(1ms);

        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_ENTRY_MODE_SET |
                               DISPLAY_IR_ENTRY_MODE_SET_INCREMENT |
                               DISPLAY_IR_ENTRY_MODE_SET_NO_SHIFT);
        ThisThread::sleep_for(1ms);

        this->send_command(DISPLAY_RS_INSTRUCTION,
                           DISPLAY_IR_DISPLAY_CONTROL |
                               DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_ON |
                               DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF |
                               DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF);
        ThisThread::sleep_for(1ms);
    };
    /**
     * @brief Imprime una cadena de texto en la posición actual del cursor.
     *
     * @param str Cadena de texto a imprimir
     */
    void print(const char *str)
    {

        if (this->line_wrap)
        {
            int string_length = strlen(str);
            int available_rows = LCD_ROWS - this->cursor_position.y_pos;
            int string_index = 0;
            while (available_rows > 0)
            {
                int available_space = LCD_COLS - this->cursor_position.x_pos;
                while (available_space > 0 && string_length > 0)
                {
                    this->send_command(DISPLAY_RS_DATA, str[string_index]);
                    string_index++;
                    string_length--;
                    available_space--;
                }
                this->cursor(0, this->cursor_position.y_pos + 1);
                available_rows--;
            }
        }
        else
        {
            while (*str)
            {
                this->send_command(DISPLAY_RS_DATA, *str++);
            }
        }
    };
    /**
     * @brief Imprime un número entero en la posición actual del cursor.
     *
     * @param value número entero a imprimir.
     */
    void print(const int value)
    {
        char buffer[10];
        itoa(value, buffer, 10);
        this->print(buffer);
    };
    /**
     * @brief Imprime un número flotante en la posición actual del cursor.
     *
     * @param value número flotante a imprimir.
     * @param precision Cantidad de decimales luego de la coma.
     */
    void print(const float value, int precision)
    {
        char buffer[10];
        ftoa(value, buffer, precision);
        this->print(buffer);
    };
    /**
     * @brief Mueve el cursor
     *
     * @param charPositionX Nueva columna a ocupar. No debe ser mayor que LCD_COLS
     * @param charPositionY Nueva fila  a ocupar. No debe ser mayor que LCD_ROWS.
     */
    void cursor(uint8_t charPositionX, uint8_t charPositionY)
    {
        this->cursor_position.x_pos = charPositionX;
        this->cursor_position.y_pos = charPositionY;
        switch (charPositionY)
        {
        case 0:
            this->send_command(DISPLAY_RS_INSTRUCTION,
                               DISPLAY_IR_SET_DDRAM_ADDR |
                                   (DISPLAY_20x4_LINE1_FIRST_CHARACTER_ADDRESS +
                                    charPositionX));
            ThisThread::sleep_for(1ms);
            break;

        case 1:
            this->send_command(DISPLAY_RS_INSTRUCTION,
                               DISPLAY_IR_SET_DDRAM_ADDR |
                                   (DISPLAY_20x4_LINE2_FIRST_CHARACTER_ADDRESS +
                                    charPositionX));
            ThisThread::sleep_for(1ms);
            break;

        case 2:
            this->send_command(DISPLAY_RS_INSTRUCTION,
                               DISPLAY_IR_SET_DDRAM_ADDR |
                                   (DISPLAY_20x4_LINE3_FIRST_CHARACTER_ADDRESS +
                                    charPositionX));
            ThisThread::sleep_for(1ms);
            break;

        case 3:
            this->send_command(DISPLAY_RS_INSTRUCTION,
                               DISPLAY_IR_SET_DDRAM_ADDR |
                                   (DISPLAY_20x4_LINE4_FIRST_CHARACTER_ADDRESS +
                                    charPositionX));
            ThisThread::sleep_for(1ms);
            break;
        }
    };
    /**
     * @brief Construye un nuevo objecto hd44780 I2Cexp
     *
     * @param sda pin con el system data de la interfaz I2C.
     * @param scl pin con el system clock de la interfaz I2C.
     */
    hd44780_I2Cexp(PinName sda, PinName scl) : pcf8574_i2c(sda, scl){};

private:
    /**
     * @brief Variable que es seteada en true cuando los 8 bits iniciales fueron enviados
     *
     */
    bool is_initial_8bit_complete = false;
    /**
     * @brief Variable que es seteada en true cuando se habilita la envoltura automática de texto.
     *
     */
    bool line_wrap = false;
    /**
     * @brief Posición del cursor
     *
     */
    coordinates_t cursor_position;
    /**
     * @brief Variables del integrado PCF8574
     *
     */
    pcf8574_t pcf8574_data;
    /**
     * @brief Objeto I2C para la comunicación con el expansor
     *
     */
    I2C pcf8574_i2c;
    /**
     * @brief Envía un comando mediante interfaz I2C al expansor.
     *
     * @param type Booleano para establecer si el comando el del tipo DISPLAY_RS_INSTRUCTION o no.
     * @param dataBus Bus de datos donde escribir la instrucción.
     */
    void send_command(bool type, uint8_t dataBus)
    {

        if (type == DISPLAY_RS_INSTRUCTION)
            this->pin_write(DISPLAY_PIN_RS, DISPLAY_RS_INSTRUCTION);
        else
        {
            this->pin_write(DISPLAY_PIN_RS, DISPLAY_RS_DATA);
        }
        this->pin_write(DISPLAY_PIN_RW, DISPLAY_RW_WRITE);
        this->write_data_bus(dataBus);
    }
    /**
     * @brief Escribe en los pines del LCD mediante interfaz I2C.
     *
     * @param dataBus información a escribir.
     */
    void write_data_bus(uint8_t dataBus)
    {
        this->pin_write(DISPLAY_PIN_EN, 0);
        this->pin_write(DISPLAY_PIN_D7, dataBus & 0b10000000);
        this->pin_write(DISPLAY_PIN_D6, dataBus & 0b01000000);
        this->pin_write(DISPLAY_PIN_D5, dataBus & 0b00100000);
        this->pin_write(DISPLAY_PIN_D4, dataBus & 0b00010000);

        if (this->is_initial_8bit_complete == true)
        {
            this->pin_write(DISPLAY_PIN_EN, 1);
            ThisThread::sleep_for(1ms);
            this->pin_write(DISPLAY_PIN_EN, 0);
            ThisThread::sleep_for(1ms);
            this->pin_write(DISPLAY_PIN_D7, dataBus & 0b00001000);
            this->pin_write(DISPLAY_PIN_D6, dataBus & 0b00000100);
            this->pin_write(DISPLAY_PIN_D5, dataBus & 0b00000010);
            this->pin_write(DISPLAY_PIN_D4, dataBus & 0b00000001);
        }

        this->pin_write(DISPLAY_PIN_EN, 1);
        ThisThread::sleep_for(1ms);
        this->pin_write(DISPLAY_PIN_EN, 0);
        ThisThread::sleep_for(1ms);
    }
    /**
     * @brief Escribe para fijar el valor de cada pin del LCD individualmente
     *
     * @param pin Pin a escribir
     * @param value Valor a escribir en el pin deseado.
     */
    void pin_write(int pin, int value)
    {

        switch (pin)
        {
        case DISPLAY_PIN_D4:
            this->pcf8574_data.displayPinD4 = value;
            break;
        case DISPLAY_PIN_D5:
            this->pcf8574_data.displayPinD5 = value;
            break;
        case DISPLAY_PIN_D6:
            this->pcf8574_data.displayPinD6 = value;
            break;
        case DISPLAY_PIN_D7:
            this->pcf8574_data.displayPinD7 = value;
            break;
        case DISPLAY_PIN_RS:
            this->pcf8574_data.displayPinRs = value;
            break;
        case DISPLAY_PIN_EN:
            this->pcf8574_data.displayPinEn = value;
            break;
        case DISPLAY_PIN_RW:
            this->pcf8574_data.displayPinRw = value;
            break;
        case DISPLAY_PIN_A_PCF8574:
            this->pcf8574_data.displayPinA = value;
            break;
        default:
            break;
        }

        this->pcf8574_data.data = 0b00000000;
        if (this->pcf8574_data.displayPinRs)
            this->pcf8574_data.data |= 0b00000001;
        if (this->pcf8574_data.displayPinRw)
            this->pcf8574_data.data |= 0b00000010;
        if (this->pcf8574_data.displayPinEn)
            this->pcf8574_data.data |= 0b00000100;
        if (this->pcf8574_data.displayPinA)
            this->pcf8574_data.data |= 0b00001000;
        if (this->pcf8574_data.displayPinD4)
            this->pcf8574_data.data |= 0b00010000;
        if (this->pcf8574_data.displayPinD5)
            this->pcf8574_data.data |= 0b00100000;
        if (this->pcf8574_data.displayPinD6)
            this->pcf8574_data.data |= 0b01000000;
        if (this->pcf8574_data.displayPinD7)
            this->pcf8574_data.data |= 0b10000000;
        this->pcf8574_i2c.write(this->pcf8574_data.address, &this->pcf8574_data.data, 1);
    }
};

#endif