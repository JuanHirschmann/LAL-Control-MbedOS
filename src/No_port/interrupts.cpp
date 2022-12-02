#include "interrupts.h"
void setup_int0_interrupt(uint8_t pin, uint8_t mode, void (*callback)(), int interrupt_mode)
{

    pinMode(pin, mode);
    attachInterrupt(digitalPinToInterrupt(pin), callback, interrupt_mode);
}
void setup_timer1_interrupt()
{

    // set timer1 interrupt at 1Hz
    cli();
    TCCR1A = 0;
    TCCR1B = 0;                          // RESET registros TCCR1x
    TCNT1 = 0;                           // RESET contador
    OCR1A = 0xF424;                      // Valor captura
    TCCR1B = (1 << WGM12) | (1 << CS12); // Modo CTC y prescale
    TIMSK1 = (1 << OCIE1A);              // habilita interrupciones
    sei();
}
void setup_pinct_portb_interrupt()
{
    cli();
    PCICR|=0x01; //Port b
    PCMSK0|=0x03; //Pines D9 y D8;
    sei();
}