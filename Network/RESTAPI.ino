/*
Author: Leon Tan

APIs, explanations and sample code for REST
*/

// Sample code: Control LED
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Wi-Fi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Initialize WebServer on port 80
AsyncWebServer server(80);

int ledPin = 2; // GPIO Pin for the LED

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Route for turning the LED ON
  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH); // Turn on LED
    request->send(200, "text/plain", "LED is ON");
  });

  // Route for turning the LED OFF
  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW); // Turn off LED
    request->send(200, "text/plain", "LED is OFF");
  });
  
  // Route to get LED status
  server.on("/led/status", HTTP_GET, [](AsyncWebServerRequest *request){
    String status = digitalRead(ledPin) ? "ON" : "OFF";
    request->send(200, "text/plain", "LED is " + status);
  });

  // Start the server
  server.begin();
}

void loop() {
  // Nothing required in the loop since we're using AsyncWebServer
}

// Sample code: Sending data to a REST API using POST
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Simulated sensor value
  int sensorValue = analogRead(34); // Replace with actual sensor read
 
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://jsonplaceholder.typicode.com/posts"); // Example API URL
    http.addHeader("Content-Type", "application/json"); // Specify content type

    // JSON payload
    String payload = "{\"sensor\":\"temperature\", \"value\":" + String(sensorValue) + "}";

    // Send HTTP POST request
    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode); // Print HTTP response code
      Serial.println(response); // Print server response
    } else {
      Serial.println("Error on sending POST");
    }
    http.end(); // Free resources
  }  
}

void loop() {
  // Nothing required in the loop for this example
}

// Sample code: Fetching data from a REST API using GET
#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("http://jsonplaceholder.typicode.com/posts/1"); // Example API URL

    int httpResponseCode = http.GET(); // Send HTTP GET request
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode); // Print response code
      Serial.println(response); // Print response payload
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end(); // Free resources
  }
}

void loop() {
  // Nothing required in the loop for this example
}
