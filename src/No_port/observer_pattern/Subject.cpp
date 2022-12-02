/**
 * @file Subject.cpp
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "observer_pattern/subjects/Subject.h"
void Subject::attach(Observer_interface *obs)
{

    this->observers[this->current_observers] = obs;
    this->current_observers++;
};
void Subject::notify_observers()
{
    for (int i = 0; i <= this->current_observers; i++)
    {
        this->observers[i]->update(this);
    }
};