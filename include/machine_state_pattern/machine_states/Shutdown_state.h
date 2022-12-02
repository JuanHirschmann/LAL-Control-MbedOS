/**
 * @file Shutdown_state.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase de estado de apagado del sistema
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef SHUTDOWN_STATE_H
#define SHUTDOWN_STATE_H
#include "Control_system.h"
#include "machine_state_pattern/machine_states/Abstract_state.h"
#include "machine_state_pattern/machine_states/Idle_state.h"
class Shutdown_state : public Abstract_state
{
private:
public:
    /**
     * @brief Actualización de estado, no hace nada.
     *
     * @param machine Máquina de estados.
     */
    virtual void update(Control_system *machine);
    /**
     * @brief Entrada al estado, apaga los LEDS, la pantalla y apaga el motor.
     *
     * @param machine
     */
    virtual void enter(Control_system *machine);
    /**
     * @brief Salida del estado, resetea las variables del sistema e incializa la pantalla.
     *
     * @param machine
     */
    virtual void exit(Control_system *machine);
    /**
     * @brief Transicion de estados
     *
     * @param machine Máquina de estados
     * @return Abstract_state*
     * Transiciones posibles:
     * La única transición posible es hacia Idle_state cuando se haya bajado la solicitud de
     *  apagado (machine->context.shutdown_request==false)
     */
    virtual Abstract_state *transition(Control_system *machine);
};
#endif