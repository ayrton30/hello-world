#include "LED.h"

LED::LED(int pin)
{
  pinMode(pin, OUTPUT); //definir pin como salida
  LEDPin = pin;
}

int LED::leerPin()
{
  int valor = 0;
  valor = digitalRead(LEDPin);
  return valor;
}

void LED::escribirPin(int valor)
{
  digitalWrite(LEDPin, valor);	// sets the LED to the value
}
