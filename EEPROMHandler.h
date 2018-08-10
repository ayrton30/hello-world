/*
  EEPROMHandler - Libreria para poder hacer uso de la memoria no volatil EEPROM.
*/

#ifndef EEPROMHandler_h
#define EEPROMHandler_h

#include "Arduino.h"
#include <EEPROM.h>

void grabarEEPROM (int direccion, String s, int longitud);
String leerEEPROM (int direccion, int longitud);

#endif