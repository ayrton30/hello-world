/*
  ServidorWeb - Libreria para crear un servidor web con el uso del hardware ESP8266.
*/

#ifndef ServidorWeb_h
#define ServidorWeb_h

#include "Arduino.h"
#include <ESP8266WebServer.h>
#include "EEPROMHandler.h"

void paginaconfig();
void guardarconfig(); // se hace uso de la libreria EEPROMHandler para guardar datos del servidor
void modoConfiguracion(const char* ssid, const char* pass);

String getPagina(); // Código HTML para el servidor
String getPaginaFin();
    
#endif
