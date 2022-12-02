/**
 * @file Abstract_state.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase de estado abstracta
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ABSTRACT_STATE_H
#define ABSTRACT_STATE_H
class Control_system;
/**
 * @brief Clase base para implementar los estados de Control_system.
 * Cada estado se debe ocupar de su comportamiento: debe leer las variables de interés de Control_system, debe actualizarse
 * y debe transicionar hacia otros estados.
 *
 */
class Abstract_state
{
public:
    /**
     * @brief Método para actualizar el estado.
     *
     * @param machine máquina de estados.
     */
    virtual void update(Control_system *machine) = 0;
    /**
     * @brief Método que se llama al ingresar al estado
     *
     * @param machine máquina de estados.
     */
    virtual void enter(Control_system *machine) = 0;
    /**
     * @brief Método que se llama al salir del estado
     *
     * @param machine máquina de estados.
     */
    virtual void exit(Control_system *machine) = 0;
    /**
     * @brief Método para cambiar de estado
     *
     * @param machine máquina de estados.
     * @return Abstract_state* Nuevo estado
     */
    virtual Abstract_state *transition(Control_system *machine) = 0;
    virtual ~Abstract_state(){};

private:
};
#endif