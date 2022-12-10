/**
 * @file Instruction_observer.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "observer_pattern/observers/Instruction_observer.h"
void Instruction_observer::update(Control_system *subject)
{
    if (subject->is_next_step_requested() && !subject->is_next_step_overriden())
    {
        subject->next_step();
    }
};