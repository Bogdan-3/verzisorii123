#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Black Network Pro";
const char* password = "00000000";

WebServer server(80);

int myValue = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());S

  server.on("/", handleRoot);
  server.on("/get_value", []() {
    myValue++; // Increment the value for demonstration
    server.send(200, "text/plain", String(myValue));
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String htmlPage = "<html>\n"
                    "<head>\n"
                    "<title>Value Update</title>\n"
                    "<script>\n"
                    "function updateValue() {\n"
                    "  fetch('/get_value')\n"
                    "  .then(response => response.text())\n"
                    "  .then(data => {\n"
                    "    document.getElementById('valueDisplay').innerHTML = data;\n"
                    "  });\n"
                    "}\n"
                    "setInterval(updateValue, 1000); // Update value every second\n"
                    "</script>\n"
                    "</head>\n"
                    "<body>\n"
                    "<h1>Dynamic Value Update</h1>\n"
                    "<p>Value: <span id=\"valueDisplay\">0</span></p>\n"
                    "</body>\n"
                    "</html>";

  server.send(200, "text/html", htmlPage);
}
