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
  WiFiClient client = server.available(); // Acepta nuevas conexiones de clientes
  
  if (!client) {
    return;
  }
  
  Serial.println("Nuevo cliente");
  
  while (!client.available()) { // Espera hasta que el cliente envíe datos
    delay(1);
  }
  
  String peticion = client.readStringUntil('\r'); // Lee la petición del cliente hasta el carácter '\r'
  Serial.println(peticion);
  client.flush();
  
  // Leer valor analógico
  int valorAnalogico = analogRead(PinAnalogico);

  if (valorAnalogico >= 800) { // Si la petición contiene '/LED=EN'
    estado = LOW; // Establece el estado del LED como apagado
  }
  
  if (valorAnalogico <= 800) { // Si la petición contiene '/LED=APA'
    estado = HIGH; // Establece el estado del LED como encendido
  }
  
  digitalWrite(PinLED, estado); // Controla el LED según el estado
  
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
  client.println("<h2>Estado del LED:</h2>");
  client.println("<input type='text' id='ledStatus' value='" + String(estado == HIGH ? "Encendido" : "Apagado") + "' readonly>");
  client.println("</body>");
  client.println("</html>");
  
  delay(1);
  Serial.println("Petición finalizada");
  Serial.println("");
}