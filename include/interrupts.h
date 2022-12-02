/**
 * @file interrupts.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Configuración de interrupciones.
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef INTERRUPTS_H
#define INTERRUPTS_H
#include <Arduino.h>
/**
 * @brief configura la interrupción interna en int0
 *
 * @param pin
 * @param mode modo del pin
 * @param callback función a llamar cuando sucede la interrupción
 * @param interrupt_mode modo de la interrupción (HIGH,LOW,RISING,FALLING)
 */
void setup_int0_interrupt(uint8_t pin, uint8_t mode, void (*callback)(), int interrupt_mode);
/**
 * @brief Configura la interrupción del timer 1 para realizarse cada 1 segundo.
 *
 */
void setup_timer1_interrupt();
void setup_pinct_portb_interrupt();
#endif