/*
  HC-SR04 - Libreria para usar el sensor de distancia ultrasónico.
*/

#ifndef Ultrasonico_h
#define Ultrasonico_h

#include "Arduino.h"

class Ultrasonico
{
  public:
    Ultrasonico(int trigger, int echo);
    int distancia();  // Calcula la distancia 
    int distanciaP(int n); // Calculo de la distancia promedio a partir de n muestras
  private:
    int triggerPin;
    int echoPin;
};

#endif
