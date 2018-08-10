#include "DS18B20.h"

sensorTemperatura::sensorTemperatura(int pin)
{
  //para manejar DS18B20
  OneWire ourWire(pin); //Se establece el pin declarado como bus para la comunicaci�n OneWire
  DallasTemperature sensorTemp(&ourWire); //Se instancia la librer�a DallasTemperature
  
  sensor = sensorTemp; //sensor es atributo de la clase
  sensor.begin(); //Se inician los sensores

  dataPin = pin;
  
}

float sensorTemperatura::temperatura()
{
  float temp = 0;
  sensor.requestTemperatures(); //Prepara el sensor para la lectura

  temp = sensor.getTempCByIndex(0);
  return temp;
}
