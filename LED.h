/*
  LED - Libreria para usar un pin de Arduino como LED.
*/

#ifndef LED_h
#define LED_h

#include "Arduino.h"

class LED
{
  public:
    LED(int pin);
    int leerPin();			//Se lee el valor HIGH o LOW del pin
    void escribirPin(int valor);	//Se escribe en LEDPin el valor
  private:
    int LEDPin;
};

#endif