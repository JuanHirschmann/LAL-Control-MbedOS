/**
 * @file Motor_control_state.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase de estado de control del motor.
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MOTOR_CONTROL_STATE_H
#define MOTOR_CONTROL_STATE_H
#include "Control_system.h"
#include "machine_state_pattern/machine_states/Abstract_state.h"
#include "machine_state_pattern/machine_states/Idle_state.h"
class Motor_control_state : public Abstract_state
{
private:
public:
    /**
     * @brief Actualización, cambia el color del LED según el estado del motor y hace sonar la alarma. Si no hay alarma
     * muestra el texto de la actualización. Enciende o apaga el motor según en que paso del procedimiento se encuentra.
     * BLOQUEA LA INTERFAZ HASTA QUE LA TEMPERATURA EN EL MOTOR SE REDUZCA POR DEBAJO DEL UMBRAL DE ADVERTENCIA.
     *
     * @param machine Máquina de estados.
     */
    virtual void update(Control_system *machine);
    /**
     * @brief Entrada al estado, enciende el LED de estado del motor.
     *
     * @param machine Máquina de estados.
     */
    virtual void enter(Control_system *machine);
    /**
     * @brief Salida del estado, apaga LEDs y Buzzer
     *
     * @param machine
     */
    virtual void exit(Control_system *machine);
    /**
     * @brief Transición de estados.
     *
     * @param machine
     * @return Abstract_state*
     * Transiciones posibles:
     * Si existe una alarma el sistema transiciona hacia Shutdown_state.
     * Si no existe alarama, cuando se supere el paso de enfriamiento del motor o no haya advertencia
     * el sistema transiciona hacia Idle_state.
     */
    virtual Abstract_state *transition(Control_system *machine);
};
#endif