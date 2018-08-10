/*
  DS18B20 - Libreria para usar el sensor de temperatura.
*/

#ifndef sensorTemperatura_h
#define sensorTemperatura_h

#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>

class sensorTemperatura
{
  public:
    sensorTemperatura(int pin);
    float temperatura();  // Calcula la temperatura
  private:
    int dataPin;
    DallasTemperature sensor; // Se hace uso de la libreria DallasTemperature.h
};

#endif