#include "ServidorWeb.h"

#define TAM 50  // Tamaño para las cadenas de caracteres

ESP8266WebServer servidor(80);

String getPagina()
{
  String pagina = "<!DOCTYPE html>"
                "<html>"
                "<head>"
                "<title>Tutorial Eeprom</title>"
                "<meta charset='UTF-8'>"
                "</head>"
                "<body>"
                "</form>"
                "<form action='guardar_conf' method='get'>"
                "SSID:<br><br>"
                "<input class='input1' name='ssid' type='text'><br>"
                "PASSWORD:<br><br>"
                "<input class='input1' name='pass' type='password'><br><br>"
                "MQTT_SERVER:<br><br>"
                "<input class='input1' name='mqtt_server' type='text'><br><br>"
                "topicLED:<br><br>"
                "<input class='input1' name='t_sensorLED' type='text'><br><br>"
                "topicTemp:<br><br>"
                "<input class='input1' name='t_sensorTemperatura' type='text'><br><br>"
                "topicDistancia:<br><br>"
                "<input class='input1' name='t_sensorDistancia' type='text'><br><br>"
                "<input class='boton' type='submit' value='GUARDAR'/><br><br>";
  return pagina;
}

String getPaginaFin()
{
  String paginafin = "</body>"
                   "</html>";
  return paginafin;
}

void paginaconfig() 
{
  String pagina = getPagina();
  String paginafin = getPaginaFin();
  
  servidor.send(200, "text/html", pagina + paginafin);
}

void guardarconfig() 
{
  // Recibimos los valores que envia por GET el formulario web
  grabarEEPROM(0, servidor.arg("ssid"), TAM);
  grabarEEPROM(50, servidor.arg("pass"), TAM);
  grabarEEPROM(100, servidor.arg("mqtt_server"), TAM);
  grabarEEPROM(150, servidor.arg("t_sensorLED"), TAM);
  grabarEEPROM(200, servidor.arg("t_sensorTemperatura"), TAM);
  grabarEEPROM(250, servidor.arg("t_sensorDistancia"), TAM);

  paginaconfig();
}

void modoConfiguracion(const char* ssidConf, const char* passConf) 
{ 
  WiFi.softAP(ssidConf, passConf); // Se comporta como un Access-Point

  //Con server.on indicamos una función como respuesta del servidor cuando el navegador solicita cierta URL.
  servidor.on("/", paginaconfig); //esta es la pagina de configuración a verse en la app
  servidor.on("/guardar_config", guardarconfig); //Graba en la EEPROM la configuración

  servidor.begin();
  // Loop
  while (true) {
    servidor.handleClient();
  }
}

