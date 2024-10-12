/*
Author: Leon Tan

APIs, explanations and sample code for synchronous client
*/

// Sample code: Synchronous Client
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";
const char* serverName = "http://example.com/api/data";
// Replace with your server

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Make the synchronous HTTP request
  makeHttpRequest();
}

void loop() {
  // request was handled synchronously in setup
}

void makeHttpRequest() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);

    // This is a synchronous call - ESP32 waits for a response
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      String payload = http.getString();
      Serial.println("HTTP Response code: " + String(httpResponseCode));
      Serial.println("Payload: " + payload);
    } else {
      Serial.println("Error on HTTP request");
    }

    http.end(); // Close connection
  } else {
    Serial.println("WiFi Disconnected");
  }
}

// Sample code: Synchronous Server
#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

// Create a WebServer object on port 80
WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);

  // Wait until the ESP32 connects to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Define routes for the server
  server.on("/", handleRoot); // Root URL
  server.on("/status", handleStatus); // Status URL

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests synchronously
  server.handleClient();
}

// Function to handle the root URL "/"
void handleRoot() {
  Serial.println("Root request received");
  // Send a response to the client
  server.send(200, "text/plain", "Hello, this is a synchronous ESP32server!");
}

// Function to handle the URL "/status"
void handleStatus() {
  Serial.println("Status request received");
  String message = "ESP32 Status: OK\n";
  message += "Free Heap: " + String(ESP.getFreeHeap()) + " bytes\n";
  message += "WiFi Signal Strength: " + String(WiFi.RSSI()) + " dBm\n";
  // Send the response
  server.send(200, "text/plain", message);
}
