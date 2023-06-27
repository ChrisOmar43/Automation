//#include "UbidotsMicroESP8266.h"
// Este archivo incluye una actualizacion de las librerias de Ubidots y observaras
// al conectarte a Ubidots que se crea otro dispostivo (Device) automaticamente
// tienes que configurar las etiquetas segun el nuevo dispositivo que se crea
// y adicionar la variable var_led  .... todo lo demás es identico 

#include "Ubidots.h"

#define DEVICE  "esp8266_principal"  // Put here your Ubidots device label
#define VARIABLE  "foto-resistencia"  // Put here your Ubidots variable label
#define ID_TEMP "foto-resistencia" 
#define TOKEN  "BBFF-IDfgdKZWhcF63zlmLtj9PjidrRqQYh"  // Put here your Ubidots TOKEN

#define WIFISSID "Anestesia" // Put here your Wi-Fi SSID
#define PASSWORD "***" // Put here your Wi-Fi password

Ubidots client(TOKEN);
int Valor_Luz = 0;

void setup() {
  Serial.begin(115200); 
  //client.wifiConnection(WIFISSID, PASSWORD);
  client.wifiConnect(WIFISSID, PASSWORD);
}

void loop() 
{
  Valor_Luz = analogRead(A0);

  client.add(ID_TEMP, Valor_Luz); 
  client.send();
  delay(2000);
}