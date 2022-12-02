/**
 * @file Subject_interface.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase para interfaz para implementar el sujeto.
 * @version 0.1
 * @date 2022-11-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _SUBJECT_INTERFACE_H_
#define _SUBJECT_INTERFACE_H_
const int MAX_OBSERVERS = 10;
class Observer_interface;
/**
 * @brief Clase interfaz para implementar el patrón de
 * diseño Observer.
 *
 */
class Subject_interface
{
protected:
    /**
     * @brief Vector de punteros a los observadores.
     *
     */
    Observer_interface *observers[MAX_OBSERVERS];

public:
    /**
     * @brief Método virtual puro para que las clases herederas
     *  implementen el agregado de observadores.
     *
     * @param obs Observador a agregar, recibido como puntero.
     */
    virtual void attach(Observer_interface *obs) = 0;
    /**
     * @brief Método virtual puro para que las clases herederas
     *  implementen la actualización de observadores.
     *
     */
    virtual void notify_observers() = 0;
};
#endif