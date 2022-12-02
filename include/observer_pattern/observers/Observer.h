/**
 * @file Observer.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase observador.
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "observer_pattern/subjects/Subject_interface.h"
#include "observer_pattern/observers/Observer_interface.h"
/**
 * @brief Clase Observer, utilizada como base del observador
 * en una implementación del patrón de diseño Observer.Hereda
 * de la interfaz de Observer.
 *
 */
class Observer : public Observer_interface
{
public:
    /**
     * @brief Implementación vacía del método de actualización, necesaria
     * para instanciar clases concretas.
     *
     * @param subject_interface Objecto a observar, recibido como puntero.
     */
    virtual void update(Subject_interface *subject_interface){};
};

#endif