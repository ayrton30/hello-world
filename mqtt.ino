#include "HCSR04.h"
#include "DS18B20.h"
#include "LED.h"
#include "EEPROMHandler.h"
#include "MQTT.h"

#include <ESP8266WiFi.h> // incluyendo la libreria ESP8266WiFi. Esta provee rutinas de Wi-Fi especificas que estas llamando para conectarnos 
#include <PubSubClient.h>

#define MODOFABRICA 1 // 1 = Se utilizan para el MQTT los valores hardcodeados por defecto
                      // 0 = Se utiliza los valores almacenados en la EEPROM
#define TAM 50        // Tamaño para las cadenas de caracteres

// Instancias de las clases
Ultrasonico sDistancia(1,2);        // (triggerPin, echoPin) 
sensorTemperatura sTemperatura(3);  // (dataPin)
LED led(5);                         // (ledPin)

WiFiClient espClient;
PubSubClient client(espClient);

// Variables por defecto
const char* mqtt_server_d = "mqtt.fi.mdp.edu.ar";
const char* t_sensorLED_d = "livra/poo/tp2017/estado_led";
const char* t_sensorTemperatura_d = "livra/poo/tp2017/temperatura";
const char* t_sensorDistancia_d = "livra/poo/tp2017/distancia";

// Datos para el modo Access-Point
const char *ssidConf = "configuracion";
const char *passConf = "123456789";

void setup() {
  Serial.begin(115200); //para la comunicación serial
  EEPROM.begin(512);

  if(intentoConexion() == false)
  {
    modoConfiguracion(ssidConf, passConf);
    intentoConexion();
  }

  if(MODOFABRICA == 1)
  {
    client.setServer(mqtt_server_d, 1883);
  }
  else
  {
    char mqtt_server[TAM];
    leerEEPROM(100, TAM).toCharArray(mqtt_server, TAM);
    client.setServer(mqtt_server, 1883);
  }
  client.setCallback(callback); // cuando se recibe un mensaje
}

void loop() 
{
  int d_LED = 0;
  int d_distancia = 0;
  float d_temperatura = 0;
  
  char msg[50]; //para publicar el mensaje
  // Variables guardadas en la EEPROM
  char t_sensorLED[TAM]; char t_sensorTemperatura[TAM]; char t_sensorDistancia[TAM];
  
  //Valores a publicar
  d_distancia = sDistancia.distanciaP(10); //Calculo de la distancia a partir de 10 muestras
  d_temperatura = sTemperatura.temperatura();
  d_LED = led.leerPin();

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (MODOFABRICA == 1) //utilizo valores por defecto
  {
    snprintf (msg, 75, "LED: %d", d_LED);
    client.publish(t_sensorLED_d, msg);
    snprintf (msg, 75, "Distancia: %d", d_distancia);
    client.publish(t_sensorDistancia_d, msg);
    snprintf (msg, 75, "Temperatura: %f", d_temperatura);
    client.publish("t_sensorTemperatura_d", msg);
  }
  else //Se utilizan los valores en la EEPROM
  {
    leerEEPROM(150, TAM).toCharArray(t_sensorLED, TAM);
    leerEEPROM(200, TAM).toCharArray(t_sensorTemperatura, TAM);
    leerEEPROM(250, TAM).toCharArray(t_sensorDistancia, TAM);
  
    snprintf (msg, 75, "LED: %d", d_LED);
    client.publish(t_sensorLED, msg);
    snprintf (msg, 75, "Distancia: %d", d_distancia);
    client.publish(t_sensorDistancia, msg);
    snprintf (msg, 75, "Temperatura: %f", d_temperatura);
    client.publish("t_sensorTemperatura", msg);
  }
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  // El dato recibido en el topic a suscribir será númerico de dos valores posibles: 1 para encender el led y 0 para apagarlo.
  if ((char)payload[0] == '1') 
  {
    led.escribirPin(HIGH);
  } else 
  {
    led.escribirPin(LOW);
  }
}

void reconnect()
{
  // Loop hasta que logramos conectar
  while (!client.connected()) 
  {
    Serial.print("Intentando conectar MQTT...");
    
    //Intento de conexion
    if (client.connect("ESP8266Client")) {
      client.subscribe(t_sensorLED_d);
    } else {
      delay(5000);
    }
  }
}
