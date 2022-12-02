/**
 * @file Subject.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "observer_pattern/subjects/Subject_interface.h"
#include "observer_pattern/observers/Observer_interface.h"
/**
 * @brief Clase base para crear sujetos a observar, hereda
 * de la interfaz Subject_interface.
 *
 */
class Subject : public Subject_interface
{
public:
    /**
     * @brief Método para agregar observadores al sujeto a implementar.
     *
     * @param obs Observador recibido como puntero.
     */
    void attach(Observer_interface *obs);
    /**
     * @brief Método que actualiza a todos los observadores presentes
     *  en el sujeto.
     *
     */
    void notify_observers();

protected:
    int current_observers = 0;
};

#endif