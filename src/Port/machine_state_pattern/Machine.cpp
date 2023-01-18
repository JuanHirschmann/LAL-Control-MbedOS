/**
 * @file Machine.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Implementación de Machine.h
 * @version 0.1
 * @date 2023-01-18
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "machine_state_pattern/Machine.h"
Machine::Machine()
{
    // this->current_state = new Idle_state();
}
/* void Machine::transition_state()
{
    Abstract_state *state = this->current_state->transition(this);
    if (state != nullptr)
    {
        delete this->current_state;
        this->current_state = state;
        this->current_state->enter(this);
    }
}
*/
Machine::~Machine()
{
    if (this->current_state != nullptr)
    {
        delete this->current_state;
    }
}