/**
 * @file Instruction_observer.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Observador de instrucciones.
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef INSTRUCTION_OBSERVER_H
#define INSTRUCTION_OBSERVER_H
#include "observer_pattern/observers/System_observer.h"
#include "Control_system.h"
/**
 * @brief Clase heredera de System_observer, creada para observar
 *  el estado de las instrucciones.
 *
 */
class Instruction_observer : public System_observer
{
public:
    /**
     * @brief Si el indicador de próximo paso del usuario está activo y
     * el acceso a la próxima instrucción no esté bloqueado, avanza hacia la siguiente instrucción.
     *
     * @param subject sujeto a observar.
     */
    void update(Control_system *subject);

private:
};
#endif