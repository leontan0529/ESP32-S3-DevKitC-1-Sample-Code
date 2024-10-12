/*
Author: Leon Tan

APIs, explanations and sample code for asynchronous client
*/

// Sample code: Asynchronous server
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define an asynchronous web server route
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello from ESP32 Async Server!");
  });

  // Start the asynchronous web server
  server.begin();
}

void loop() {
  // Running other code while handling server requests asynchronously
}

// Sample code: Asynchronous Client
#include <WiFi.h>
#include <AsyncTCP.h>
#include <AsyncHTTPClient.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";
const char* serverName = "http://example.com/api/data";

AsyncHTTPClient httpClient;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define the callback for when the request is complete
  httpClient.onReadyStateChange([](void *arg, AsyncHTTPClient* client, int readyState){
    if (readyState == 4) { // Response is complete
      Serial.println("Response: " + client->responseText());
    }
  });

  // Send the asynchronous HTTP request
  httpClient.open("GET", serverName);
  httpClient.send();
}

void loop() {
  // The program can continue to execute other tasks while waiting for the response
  Serial.println("ESP32 is free to do other tasks!");
  delay(5000); // Emulate some other tasks
}
