#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "Black Network Pro";
const char* password = "00000000";

// Create a WebServer object on port 80 (HTTP)
WebServer server(80);

// Sensor pins and variables
int IR = D13;
int IR2 = D12;
int IR3 = D11;
int Quantity = 0;
int Quantity2 = 0;
int Quantity3 = 0;
int last = 0;
int last2 = 0;
int last3 = 0;
int number = 0;
int number2 = 0;
int number3 = 0;

// HTML content to be served
String htmlPage = "<html>\n"
                  "<head>\n"
                  "<title>Fabrica Verzisorii123</title>\n"
                  "<script>\n"
                  "function updateValues() {\n"
                  "  fetch('/get_values')\n"
                  "  .then(response => response.json())\n"
                  "  .then(data => {\n"
                  "    document.getElementById('Quantity').innerHTML = data.Quantity;\n"
                  "    document.getElementById('Quantity2').innerHTML = data.Quantity2;\n"
                  "    document.getElementById('Quantity3').innerHTML = data.Quantity3;\n"
                  "  });\n"
                  "}\n"
                  "function resetQuantities() {\n"
                  "  fetch('/reset')\n"
                  "  .then(() => alert('Quantities have been reset'));\n"
                  "}\n"
                  "setInterval(updateValues, 1000); // Update every second\n"
                  "</script>\n"
                  "</head>\n"
                  "<body style=\"background-image: linear-gradient(to right, cyan, yellow);text-align: center;\">\n"
                  "<h1>Fabrica de reciclare Verzisorii123</h1>\n"
                  "<center><h2>Bine ati venit la Fabrica Verzisorilor123</h2></center>\n"
                  "<h1>Deseuri Colectate</h1>\n"
                  "<h2><p style=\"color:blue\">Albastru: <span id='Quantity'>0</span></p>\n"
                  "<p style=\"color:green\">Verde: <span id='Quantity2'>0</span></p>\n"
                  "<p style=\"color:red\">Rosu: <span id='Quantity3'>0</span></p></h2>\n"
                  "<button onclick=\"resetQuantities()\">Reset Quantities</button>\n"
                  "</body>\n"
                  "</html>";


void setup() {
  Serial.begin(115200);  // Start serial communication at 115200 baud

  // Initialize the sensor pins
  pinMode(IR, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define routes
  server.on("/", handleRoot);
  server.on("/get_values", handleGetValues);
  server.on("/reset", handleReset);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Sensor monitoring and counting
  int sensorValue = digitalRead(IR);
  int sensorValue2 = digitalRead(IR2);
  int sensorValue3 = digitalRead(IR3);
  number = 0;
  number2 = 0;
  number3 = 0;

  if (sensorValue == 1){
    last = 0;
  }
  if (sensorValue2 == 1){
    last2 = 0;
  }
  if (sensorValue3 == 1){
    last3 = 0;
  }

  while (sensorValue == 0 && number == 0 && last == 0){
    Quantity = Quantity + 1;
    last = 1;
    number = number + 1;
    delay(500);
  }
  while (sensorValue2 == 0 && number2 == 0 && last2 == 0){
    Quantity2 = Quantity2 + 1;
    last2 = 1;
    number2 = number2 + 1;
    delay(500);
  }
  while (sensorValue3 == 0 && number3 == 0 && last3 == 0){
    Quantity3 = Quantity3 + 1;
    last3 = 1;
    number3 = number3 + 1;
    delay(500);
  }
}

// Handle the root URL "/"
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

// Handle the "/get_values" URL to return sensor data as JSON
void handleGetValues() {
  String jsonResponse = "{";
  jsonResponse += "\"Quantity\":" + String(Quantity) + ",";
  jsonResponse += "\"Quantity2\":" + String(Quantity2) + ",";
  jsonResponse += "\"Quantity3\":" + String(Quantity3);
  jsonResponse += "}";
  server.send(200, "application/json", jsonResponse);
}

void handleReset() {
  Quantity = 0;
  Quantity2 = 0;
  Quantity3 = 0;
  server.send(200, "text/plain", "Quantities reset");
}