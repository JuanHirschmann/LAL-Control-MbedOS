/**
 * @file Observer_interface.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase para interfaz para implementar el observador.
 * @version 0.1
 * @date 2022-11-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _OBSERVER_INTERFACE_H_
#define _OBSERVER_INTERFACE_H_
class Subject_interface;
/**
 * @brief Interfaz para implementar el patrón de diseño Observer.
 *
 */
class Observer_interface
{
public:
    /**
     * @brief Método virtual puro para que las clases herederas implementen
     * la actualización de observadores polimórficamente.
     *
     * @param subject_interface Objeto a observar recibido como puntero.
     */
    virtual void update(Subject_interface *subject_interface) = 0;
};
#endif