#include "HCSR04.h"

Ultrasonico::Ultrasonico(int trigger, int echo)
{
  pinMode(trigger, OUTPUT); // Configura el Pin de trigger como salida
  pinMode(echo, INPUT);  // Configura el Pin de echo como entrada
  triggerPin = trigger;
  echoPin = echo;
}

int Ultrasonico::distancia()
{
  long duracion = 0;
  int distancia = 0;

  //limpiamos triggerPin
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  //triggerPin en estado HIGH por 10 microsegundos
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  //lee el echoPin, devuelve el tiempo del recorrido de la onda de sonido en microsegundos
  duracion = pulseIn(echoPin, HIGH);

  distancia = duracion * 0.034 / 2;
  return distancia;
}

int Ultrasonico::distanciaP(int n_muestras)
{
  int distancias[n_muestras];
  int sumatoria = 0;
  
  for(int i=0; i<n_muestras; i++)
  {
    distancias[i] = Ultrasonico::distancia();
    sumatoria = sumatoria + distancias[i];
  }

  return (sumatoria / n_muestras);
}

