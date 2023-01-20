/**
 * @file Check_instruction_state.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Estado para el control de la ejecución de instrucciones.
 * @version 0.1
 * @date 2023-01-20
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CHECK_INSTRUCTION_STATE_H
#define CHECK_INSTRUCTION_STATE_H
#include "Control_system.h"
#include "machine_state_pattern/machine_states/Abstract_state.h"
#include "machine_state_pattern/machine_states/Alarm_state.h"

class Check_instruction_state : public Abstract_state
{
public:
    virtual void update(Control_system *machine);

    virtual void enter(Control_system *machine);

    virtual void exit(Control_system *machine);

    virtual Abstract_state *transition(Control_system *machine);
};
#endif