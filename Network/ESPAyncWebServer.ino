/*
Author: Leon Tan

APIs, explanations and sample code for ESPAsyncWebServer library
*/

// API: Initialises web server on specified port
AsyncWebServer server(PORT);

// API: Handles incoming requests to a specific route (/path) 
server.on("/path", HTTP_GET, handlerFunction);
server.on("/path", HTTP_POST, handlerFunction);

// API: Handles requests to undefined routes, returning a 404 error or custom message
server.onNotFound(handlerFunction);

// API: Creates real-time, bi-directional communication between client and server using WebSockets
server.on("/ws", HTTP_GET, WebSocket handler);

// API: Sends a plain text HTTP response with the status code
request->send(200, "text/plain", "Hello World!");

// API: Sends an HTML file from the SPIFFS (or LittleFS) filesystem
request->send(SPIFFS, "/index.html", "text/html");

// API: Handles file uploads asynchronously
server.onFileUpload([](AsyncWebServerRequest *request, const String& filename, size_t index, uint8_t *data, size_t len, bool final) {
  ...
});

// API: Serves static files
server.serveStatic("/static", SPIFFS, "/static").setCacheControl("max-age=600");

// API: Retrieves URL query parameters from an incoming request
request->getParam("key")->value();

// Sample code: WebSocket for Real-Time Data
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Web server and WebSocket server
AsyncWebServer server(80);
WebSocketsServer webSocket(81);

// Handle incoming WebSocket messages
void handleWebSocketMessage(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if(type == WStype_TEXT) {
    Serial.printf("[%u] Received: %s\n", num, payload);
    webSocket.sendTXT(num, "Message received"); // Send response back
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
 
  // Serve WebSocket requests
  webSocket.begin();
  webSocket.onEvent(handleWebSocketMessage);
 
  // Serve the WebSocket HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  request->send(200, "text/html", "<h1>WebSocket Test</h1>");
  });

  server.begin();
}

void loop() {
  webSocket.loop();
}

// Sample code: File serving with SPIFFS
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

// Network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

AsyncWebServer server(80);

void setup(){
  Serial.begin(115200);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Serve index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

  // Serve additional files (CSS, JS, etc.)
  server.serveStatic("/css", SPIFFS, "/css/");
  server.serveStatic("/js", SPIFFS, "/js/");
  server.begin();
}

void loop() {
  // Nothing needed in the loop
}


