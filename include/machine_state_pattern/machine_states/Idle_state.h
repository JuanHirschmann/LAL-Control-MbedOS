/**
 * @file Idle_state.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase de estado de reposo.
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef IDLE_STATE_H
#define IDLE_STATE_H
#include "Control_system.h"
#include "machine_state_pattern/machine_states/Abstract_state.h"
#include "machine_state_pattern/machine_states/Motor_control_state.h"
/**
 * @brief Clase para implementar el estado de reposo del sistema
 * (Sin alarmas ni advertencias, actualiza todos los observadores y la pantalla)
 *
 */
class Idle_state : public Abstract_state
{
public:
    /**
     * @brief Método para actualizar el sistema cuando está en estado de reposo.
     * Actualiza la pantalla y los observadores.
     *
     * @param machine Maquina de estados
     */
    virtual void update(Control_system *machine);
    /**
     * @brief Método llamado al ingresar al estado. Actualiza la pantalla
     * con el paso del procedimiento actual.
     *
     * @param machine máquina de estados
     */
    virtual void enter(Control_system *machine);
    /**
     * @brief Método llamada al salir del estado. Apaga los led indicadores y el buzzer.
     *
     * @param machine máquina de estados
     */
    virtual void exit(Control_system *machine);
    /**
     * @brief Transición hacia nuevo estado.
     *
     * Transiciones posibles:
     * Si se solicito una advertencia, una alarma o el sistema se encuentra entre los pasos
     * MOTOR_ON_STEP y MOTOR_COOLDOWN_STEP la transición es hacia Motor_control_state.
     * Si se solicitó un apagado del sistema y no se transiciona hacia Motor_control_state,
     * la transición es hacia Shutdown_state.
     * @param machine máquina de estados.
     * @return Abstract_state* Nuevo estado
     */
    virtual Abstract_state *transition(Control_system *machine);
};
#endif