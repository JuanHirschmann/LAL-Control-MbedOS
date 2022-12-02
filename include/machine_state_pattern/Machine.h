/**
 * @file Machine.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase de máquina abstracta.
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MACHINE_H
#define MACHINE_H
#include "machine_state_pattern/machine_states/Abstract_state.h"

/**
 * @brief Clase para base para la implementación de una máquina de estados finita.
 *
 */
class Machine
{
public:
    /**
     * @brief Construye un nuevo objecto Machine
     *
     */
    Machine();
    /**
     * @brief Método virtual para llamar al método de transición del estado actual.
     *
     */
    virtual void transition_state() = 0;
    /**
     * @brief Destruye el objecto Machine
     *
     */
    virtual ~Machine() = 0;

protected:
    /**
     * @brief Puntero al estado actual del objeto
     *
     */
    Abstract_state *current_state = nullptr;
};
#endif
