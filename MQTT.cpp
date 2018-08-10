#include "MQTT.h"
#define TAM 50        // Tamaño para las cadenas de caracteres

bool intentoConexion()
{
  int contconexion = 0; // para delimitar hasta cuanto espero la conexion
  char ssid[TAM];      
  char pass[TAM];
  
  //Leer de la EEPROM
  leerEEPROM(0, TAM).toCharArray(ssid, 50);
  leerEEPROM(50, TAM).toCharArray(pass, 50);
  
  //Intento conectarme con los datos grabados en la EEPROM
  WiFi.mode(WIFI_STA); //station mode para conectarse a una network especifica
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED and contconexion < 50) // Cuenta hasta 50 si no se puede conectar lo cancela
  { 
    ++contconexion;
    delay(100);
  }
  
  if (contconexion > 50)
  {
    //Se termino el tiempo de espera, entro al modo Acces-Point |Modo Configuración|
    return false;
  }

  return true;
}



