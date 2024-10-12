/*
Author: Leon Tan

APIs, explanations and sample code for WebSocket
*/

// Sample code: Simple WebSocket server
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

// WiFi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// WebSocket instance
AsyncWebServer server(80);
AsyncWebSocket ws("/ws"); // WebSocket server endpoint at /ws

// Callback to handle WebSocket events
void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
  AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
    client->text("Hello from ESP32 WebSocket server!");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
  } else if (type == WS_EVT_DATA) {
    Serial.printf("Data received: %s\n", (char*)data);
    client->text("Message received: " + String((char*)data));
  }
}

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Setup WebSocket event handler
  ws.onEvent(onWsEvent);

  // Add WebSocket to the web server
  server.addHandler(&ws);
 
  // Start the web server
  server.begin();
}

void loop() {
  // Cleanup disconnected clients
  ws.cleanupClients();
}

// Sample code: WebServer Client (HTML/JS)
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 WebSocket Demo</title>
  <script>
    var ws;

    function initWebSocket() {
      ws = new WebSocket('ws://' + window.location.hostname + '/ws');

      ws.onopen = function() {
        document.getElementById('status').innerHTML = "WebSocket connection established";
      };

      ws.onmessage = function(event) {
        document.getElementById('messages').innerHTML += '<br>' + event.data;
      };

      ws.onclose = function() {
        document.getElementById('status').innerHTML = "WebSocket connection closed";
      };
    }

    function sendMessage() {
      var message = document.getElementById('msg').value;
      ws.send(message);
    }
  </script>
</head>
<body onload="initWebSocket();">
  <h1>ESP32 WebSocket Demo</h1>
  <p id="status">Connecting...</p>
  <div>
    <input type="text" id="msg" placeholder="Type a message">
    <button onclick="sendMessage()">Send Message</button>
  </div>
  <div id="messages">
    <h2>Messages:</h2>
  </div>
</body>
</html>

// Sample code: Real-time sensor data monitoring
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_CONNECT) {
    Serial.println("WebSocket client connected");
  } else if (type == WS_EVT_DISCONNECT) {
    Serial.println("WebSocket client disconnected");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  ws.onEvent(onWsEvent);
  server.addHandler(&ws);
  server.begin();
}

void loop() {
  // Simulating sensor data (replace this with actual sensor reading)
  int sensorValue = analogRead(34); // Example for ESP32's analog pin

  // Sending sensor data to all WebSocket clients
  ws.textAll(String(sensorValue));

  // Cleanup WebSocket clients
  ws.cleanupClients();

  delay(1000); // Send data every 1 second
}

// Sample code: Real-time sensor data monitoring (HTML/JS)
<!DOCTYPE html>
<html>
<head>
  <title>Sensor Data</title>
  <script>
    var ws;

    function initWebSocket() {
      ws = new WebSocket('ws://' + window.location.hostname + '/ws');
      ws.onmessage = function(event) {
        document.getElementById('sensor').innerHTML = "Sensor Value: " + event.data;
      };
    }
  </script>
</head>
<body onload="initWebSocket();">
  <h1>Sensor Monitoring</h1>
  <p id="sensor">Waiting for data...</p>
</body>
</html>
