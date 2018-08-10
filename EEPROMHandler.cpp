#include "EEPROMHandler.h"

void grabarEEPROM(int direccion, String s, int longitud)
{
  int size = s.length();
  int i = 0;
  char inchar[50];
  
  s.toCharArray(inchar, size + 1);
  
  for (i = 0; i < size; i++) 
  {
    EEPROM.write(direccion + i, inchar[i]);
  }
//Si a partir del final del string me sobran caracteres grabo en la direccion de la EEPROM con el valor 255
  for (i = size; i < longitud ; i++) 
  {
    EEPROM.write(direccion + i, 255);
  }
  EEPROM.commit();
}

String leerEEPROM(int direccion, int longitud)
{
  byte lectura;
  String stringLectura;
  int i = 0;
  
  for (i = direccion; i < direccion + longitud; i++) 
  {
    lectura = EEPROM.read(i);
    
    if (lectura != 255) 
    {
      stringLectura += (char)lectura;
    }
  }

  return stringLectura;
}
