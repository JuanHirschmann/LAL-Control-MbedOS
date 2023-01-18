/**
 * @file Alarm_state.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase de estado de control del motor.
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ALARM_STATE_H
#define ALARM_STATE_H
#include "Control_system.h"
#include "machine_state_pattern/machine_states/Abstract_state.h"
#include "machine_state_pattern/machine_states/Idle_state.h"
#include "machine_state_pattern/machine_states/Check_instruction_state.h"
class Alarm_state : public Abstract_state
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
     * Si no existe alarma y hay solicitud de nuevo paso el sistema transiciona hacia Check_instruction.
     */
    virtual Abstract_state *transition(Control_system *machine);
};
#endif