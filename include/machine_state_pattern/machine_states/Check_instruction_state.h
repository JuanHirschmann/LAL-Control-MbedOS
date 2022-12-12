
#ifndef CHECK_INSTRUCTION_STATE_H
#define CHECK_INSTRUCTION_STATE_H
#include "Control_system.h"
#include "machine_state_pattern/machine_states/Abstract_state.h"
#include "machine_state_pattern/machine_states/Motor_control_state.h"

class Check_instruction_state : public Abstract_state
{
public:
    virtual void update(Control_system *machine);

    virtual void enter(Control_system *machine);

    virtual void exit(Control_system *machine);

    virtual Abstract_state *transition(Control_system *machine);
};
#endif