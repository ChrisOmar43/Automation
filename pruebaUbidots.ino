/****************************************
* Include Libraries
****************************************/

#include "Ubidots.h"

/****************************************
* Define Instances and Constants
****************************************/   
 
const char* UBIDOTS_TOKEN = "BBFF-WlG8AXORNLwFjEEfMjGzFfZMMz2kLs";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "HONOR 9X Lite DFA5";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "benditoalcohol1";      // Put here your Wi-Fi password 
int PinAnalogico = A0; // Pin analógico para leer el valor

Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

/****************************************
* Auxiliar Functions
****************************************/

// Put here your auxiliar functions

/****************************************
* Main Functions
****************************************/  

void setup() {                       

  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  pinMode(PinLED, OUTPUT);
  digitalWrite(PinLED, LOW);
  Serial.println("");
  Serial.println("WiFi conectada");                    
}

void loop() {

  int value1 = analogRead(PinAnalogico);
  
  ubidots.add("Variable_Name_One", value1);// Change for your variable name  
  bool bufferSent = false;
  bufferSent = ubidots.send(); // Will send data to a device label that matches the device Id

  if (bufferSent) {
  // Do something if values were sent properly
   Serial.println("Values sent by the device");
  }
  delay(5000);
}