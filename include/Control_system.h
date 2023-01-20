/**
 * @file Control_system.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Clase Control_system, utilizada como clase central para
 * el sistema de control.
 * @version 0.1
 * @date 2023-01-20
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H
#include "observer_pattern/subjects/Subject.h"
#include "machine_state_pattern/Machine.h"
#include "drivers/Display.h"
#include "user_messages.h"
#include "observer_pattern/observers/System_observer.h"
#include "drivers/Temperature_sensor.h"
#include "drivers/Moisture_sensor.h"
#include "types.h"
#include "drivers/Buzzer.h"
#include "drivers/Motor.h"
#include "drivers/Dual_led.h"
#include "drivers/Digital_dual_led.h"
#include "drivers/Cooler.h"
#include "machine_state_pattern/machine_states/Shutdown_state.h"
class Control_system : public Subject, public Machine
{
    friend class Idle_state;
    friend class Alarm_state;
    friend class Shutdown_state;
    friend class Check_instruction_state;

public:
    /**
     * @brief Inicializa el sistema con el estado de apagado
     *
     */
    void init();
    /**
     * @brief Según la variable context.current_alarm resuelve el comportamiento de la alarma.
     * - OVERTEMP_ALARM: Enciende los ventiladores a tope, la luz de estado del motor en rojo y el buzzer.
     * Apaga el motor.
     * - HUMIDITY_ALARM: apaga motor, enciende luz de estado del motor en rojo y apaga ventiladores.
     * - HALTED_FAN_ALARM: apaga motor, enciende luz de estado del motor y los ventiladores en rojo y apaga ventiladores.
     * - NO_TEMP_SENSOR_ALARM: apaga el motor, enciende luz de estado del motor en rojo.
     * - OVERTEMP_WARNING: Fija la velocidad de los ventiladores y enciende la luz de estado del motor en amarillo.
     * - SLOW_FAN_WARNING: No implementado
     * - NO_ALARM: No realiza ninguna acción
     *
     */
    void handle_alarm();
    /**
     * @brief Realiza la transición de estados y actualiza el estado
     *
     */
    void update();
    /**
     * @brief Setea la solicitud de apagado a falso.
     *
     */
    void wake();
    /**
     * @brief Informa si el sistema está apagado o no
     *
     * @return true El sistema está apagado.
     * @return false El sistema está encendido
     */
    bool is_off();
    /**
     * @brief Resetea las variables de contexto.
     *
     */
    void reset_context();
    size_t get_cooler_rotation(int cooler);
    Context_t get_context();
    bool is_cooler_on(int cooler);
    /**
     * @brief Fija velocidades en el display de los ventiladores
     *
     * @param rear_cooler_speed velocidad del ventilador trasero [RPS]
     * @param front_cooler_speed velocidad del ventilador frontal [RPS]
     */
    void display_cooler_speed(float rear_cooler_speed, float front_cooler_speed);
    /**
     * @brief Fija el valor de velocidad del ventilador
     *
     * @param rear_cooler_speed  velocidad ventilador trasero [RPS]
     * @param front_cooler_speed velocidad ventilador delantero [RPS]
     */
    void set_cooler_speed(float rear_cooler_speed, float front_cooler_speed);
    /**
     * @brief Muestra en pantalla el paso del procedimientoa actual.
     *
     */
    void show_current_step();
    /**
     * @brief Muestra el mensaje de error por pantalla.
     *
     */
    void show_error_msg();
    /**
     * @brief Enciende el buzzer por 100ms (bloqueante) y, si no esta anulado
     * el próximo paso, avanza hacia la siguiente instrucción. Si no hay siguiente instrucción
     * se apagará el sistema.
     *
     */
    void next_step();
    /**
     * @brief Inicializa el display lcd del sistema.
     *
     */
    void init_display();
    Control_system(/* args */);
    /**
     * @brief Itera sobre todos los observadores, llamando a su método de actualización.
     *
     */
    void notify_observers() override;
    /**
     * @brief Obtiene la temperatura del objeto temp_sensor
     *
     * @return float Temperatura en Celsius de la medición un error se indica
     * con el valor -127°C
     */
    float measure_temperature();
    /**
     * @brief Obtiene la humedad del objeto mois_sensor.
     *
     * @return int Valor analógico de la medición. (0 indica humedad, 255 sequedad máxima)
     */
    int measure_moisture();
    /**
     * @brief Solicita avanzar hacia la siguiente instrucción. Si no hay
     * alguna alarma activa la solicitud se hará efectiva.
     *
     */
    void set_next_step_flag(bool new_state);
    /**
     * @brief Devuelve el estado de solicitud de próxima instrucción.
     *
     * @return true Existe una solicitud de siguiente instrucción activa.
     * @return false No existe una solicitud de siguiente instrucció  activa.
     */
    bool is_next_step_requested();
    /**
     * @brief Fija el valor del flag de muestro de sensores.
     *
     * @param new_state Nuevo estado para el flag.
     */
    void set_poll_sensors_flag(bool new_state);
    /**
     * @brief Devuelve el estado del indicador de muestreo de sensores.
     *
     * @return true Se solicitó un muestreo de sensores.
     * @return false No se solicitó un muestreo de sensores.
     */
    bool is_poll_sensors_requested();
    /**
     * @brief Fija el valor del indicador de alarma
     *
     * @param new_state Nuevo estado para el indicador de alarma.
     */
    void set_alarm_flag(bool new_state);
    /**
     * @brief Devuelve el estado del indicador de alarma.
     *
     * @return true Se solicitó una alarma.
     * @return false No se solicitó una alarma.
     */
    bool is_alarm_requested();
    /**
     * @brief Solicita una alarma.
     *
     * @param type_of_alarm Tipo de alarma a solicitar.
     */
    void request_alarm(Alarm_types type_of_alarm);
    /**
     * @brief Solicita una advertencia.
     *
     * @param type_of_alarm Tipo de advertencia a solicitar.
     */
    void request_warning(Alarm_types type_of_warning);
    /**
     * @brief Fija el valor del indicador de advertencia
     *
     * @param new_state nuevo valor del indicador de advertencia
     */
    void set_warning_flag(bool new_state);
    /**
     * @brief Devuelve el estado de solicitud de advertencia.
     *
     * @return true Existe una solicitud activa.
     * @return false No existe una solicitud activa.
     */
    bool is_warning_requested();
    /**
     * @brief Realiza la transición de estados en caso de ser
     * necesario.
     *
     */
    void transition_state();
    ~Control_system();
    bool is_next_step_overriden() { return this->context.override_next_step; };

private:
    /**
     * @brief Variable de contexto.
     * La definición del tipo de dato se encuentra en
     * types.h. Se utiliza para unificar los distintos indicadores del
     * sistema.
     *
     */
    Context_t context;
    /**
     * @brief Perifericos: Display
     *
     */
    Display display;
    /**
     * @brief Perifericos: Sensor de temperatura
     *
     */
    Temperature_sensor temp_sensor;
    /**
     * @brief Perifericos: Buzzer activo.
     *
     */
    Buzzer buzzer;
    /**
     * @brief Perifericos: Buzzer activo.
     *
     */
    Motor motor;
    /**
     * @brief Perifericos: Sensor analógico de humedad.
     *
     */
    Moisture_sensor mois_sensor;
    /**
     * @brief Perifericos: Ventilador delantero.
     *
     */
    Cooler front_cooler;
    /**
     * @brief Perifericos: Ventilador trasero.
     *
     */
    Cooler rear_cooler;
    /**
     * @brief Perifericos: LED RG de estado de motor
     *
     */
    Dual_LED motor_status_led;
    /**
     * @brief Perifericos: LED RG de estado de suministro de agua.
     *
     */
    Digital_dual_LED water_intake_led;
    /**
     * @brief Perifericos: LED RG de estado del ventilador trasero.
     *
     */
    Digital_dual_LED rear_cooler_led;
    /**
     * @brief Perifericos: LED RG de estado del ventilador delantero.
     *
     */
    Digital_dual_LED front_cooler_led;
};

#endif