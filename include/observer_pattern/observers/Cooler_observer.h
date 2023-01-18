#ifndef _COOLER_OBSERVER_H
#define _COOLER_OBSERVER_H
#include "observer_pattern/observers/System_observer.h"
#include "Control_system.h"
#include "mbed.h"
const int MAX_COOLERS = 2;
const int SAMPLE_PERIOD = 1; //[s]
/**
 * @brief Clase heredera de System_observer, creada para observar
 *  la velocidad de los ventiladores.
 *
 */
class Cooler_observer : public System_observer
{

public:
    Cooler_observer()
    {
        timer.start();
    }
    /**
     * @brief Si el indicador de próximo paso del usuario está activo y
     * el acceso a la próxima instrucción no esté bloqueado, avanza hacia la siguiente instrucción.
     *
     * @param subject sujeto a observar.
     */
    void update(Control_system *subject);
    /**
     * @brief Actualiza la medición de velocidad.
     *
     * @param subject sujeto a observar.
     */
    void update_speed(Control_system *subject);

private:
    Timer timer;
    double speed[MAX_COOLERS];
};
#endif