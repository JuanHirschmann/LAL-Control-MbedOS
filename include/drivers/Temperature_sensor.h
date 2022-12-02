/**
 * @file Temperature_sensor.h
 * @author Juan Hirschmann (jhirschmann@fi.uba.ar)
 * @brief Controlador para sensor de temperatura DS18B20
 * @version 0.1
 * @date 2022-11-02
 *
 */
#ifndef TEMPERATURE_SENSOR
#define TEMPERATURE_SENSOR

#include "system_settings.h"
#include <DS1820.h>

class Temperature_sensor
{
  /**
   * @brief Clase para el control del sensor de temperatura por interfaz OneWire
   *
   */
public:
  // Temperature_sensor(){};
  /**
   * @brief Construye un objeto Temperature_sensor.
   *
   * @param one_wire_bus Número de pin a utilizar como interfaz OneWire.
   */
  Temperature_sensor(PinName one_wire_bus);
  /**
   * @brief Obtiene la Temperatura de todos los sensores como un promedio simple (Celsius).
   *
   * @return float Temperatura promediado de los sensores (Celsius).
   */
  float get_reading();

private:
  /**
   * @brief Inicializa todos los sensores disponibles en la interaz
   *
   * @param one_wire_bus Número de pin a utilizar como interfaz OneWire.
   */
  void init_sensors();
  /**
   * @brief Actualiza el vector de temperaturas del objeto.
   *
   */
  void update_readings();
  /**
   * @brief Cantidad de sensores ds18 detectados en la interfaz OneWire
   *
   */
  int available_ds18_devices = 0;
  /**
   * @brief Vector de temperaturas leídas.
   *
   */
  float reading;
  /**
   * @brief Objeto DallasTemperature, utilizado para la interacción con sensores.
   *
   */
  DS1820 DS18B20_sensor;
};
#endif