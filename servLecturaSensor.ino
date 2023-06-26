#include <ESP8266WiFi.h>

const char* ssid = "IZZI-EB0D";
const char* password = "8871B1BBEB0D";

WiFiServer server(80);

int PinLED = 2;
int estado = LOW;

int PinAnalogico = A0; // Pin analógico para leer el valor

void setup() {
  Serial.begin(115200);
 
  pinMode(PinLED, OUTPUT);
  digitalWrite(PinLED, LOW);
  
  WiFi.begin(ssid, password);
  Serial.printf("\n\nConectando a la red: %s\n", WiFi.SSID().c_str());
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi conectada");
  
  server.begin();
  Serial.println("Servidor inicializado");
  
  Serial.printf("\n\nUtiliza esta URL para conectar: http://%s/\n", WiFi.localIP().toString().c_str());
}

void loop() {
  WiFiClient client = server.available();
  
  if (!client) {
    return;
  }
  
  Serial.println("Nuevo cliente");
  
  while (!client.available()) {
    delay(1);
  }
  
  String peticion = client.readStringUntil('\r');
  Serial.println(peticion);
  client.flush();
  
  if (peticion.indexOf('/LED=EN') != -1) {
    estado = LOW;
  }
  
  if (peticion.indexOf('/LED=APA') != -1) {
    estado = HIGH;
  }
  
  digitalWrite(PinLED, estado);
  
  // Leer valor analógico
  int valorAnalogico = analogRead(PinAnalogico);
  
  // Generar y enviar la respuesta HTTP al cliente
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<html>");
  client.println("<head>");
  client.println("<title>Valor Analógico</title>");
  client.println("<meta http-equiv='refresh' content='5'>"); // Actualizar cada 5 segundos
  client.println("</head>");
  client.println("<body>");
  client.println("<h1>Valor Analógico:</h1>");
  client.println("<h2>" + String(valorAnalogico) + "</h2>");
  client.println("</body>");
  client.println("</html>");
  
  delay(1);
  Serial.println("Peticion finalizada");
  Serial.println("");
}