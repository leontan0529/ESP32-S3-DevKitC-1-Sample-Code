/*
Author: Leon Tan

APIs, explanations and sample code for creating a web server
*/

// Sample code: Basic ESP32 Web Server with a Simple API
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

#define DHTPIN 4 // Pin where the DHT sensor is connected
#define DHTTYPE DHT11 // Change to DHT22 if you're using that sensor

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
 
  // Initialize DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define API endpoint for temperature and humidity data
  server.on("/api/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Check if readings are valid
    if (isnan(temperature) || isnan(humidity)) {
      request->send(500, "application/json", "{\"error\":\"Failed to read from DHT sensor\"}");
      return;
    }

    // Create JSON response
    String json = "{ \"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + " }";

    // Send response
    request->send(200, "application/json", json);
  });

  // Start the server
  server.begin();
}

void loop() {
  // Nothing here, as we're using asynchronous web server
}

// Sample code: Control GPIO over API
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const int ledPin = 2; // LED connected to GPIO 2

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Initialize LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Define API endpoint to turn the LED on
  server.on("/api/led/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH); // Turn LED on
    request->send(200, "application/json", "{\"status\":\"LED is ON\"}");
  });

  // Define API endpoint to turn the LED off
  server.on("/api/led/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW); // Turn LED off
    request->send(200, "application/json", "{\"status\":\"LED is OFF\"}");
  });

  // Start the server
  server.begin();
}

void loop() {
  // Nothing here, as we're using asynchronous web server
}

// Sample code: Serving a Web Page with API Interactions
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <DHT.h>

#define DHTPIN 4 // Pin where the DHT sensor is connected
#define DHTTYPE DHT11 // Change to DHT22 if you're using that sensor

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);
const int ledPin = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  } 
  Serial.println("Connected to WiFi");

  // Serve web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<h1>ESP32 Web Server</h1><button onclick=\"fetch('/api/led/on').then(() => alert('LED ON'))\">Turn ON LED</button><button onclick=\"fetch('/api/led/off').then(() => alert('LED OFF'))\">Turn OFF LED</button>");
  });

  // Define API endpoints
  server.on("/api/led/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);
    request->send(200, "application/json", "{\"status\":\"LED is ON\"}");
  });
  server.on("/api/led/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);
    request->send(200, "application/json", "{\"status\":\"LED is OFF\"}");
  });

  // Start the server
  server.begin();
}

void loop() {
  // No code in loop as it's handled by the web server
}
