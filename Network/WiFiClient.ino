/*
Author: Leon Tan

APIs, explanations and sample code from WiFiClient library
*/

// API: Creates an instance of a Wi-Fi client
WiFiClient client;

// API: Connects to a specified host and port
client.connect(host, port);
/*
host: a domain name (e.g., "example.com") or an IP address in string format (e.g., "192.168.1.10").
port: port on the remote server, which could be 80 for HTTP.
Return: true if successful, otherwise false.
*/

// API: Sends data to the connected server
client.write(data);

// API: Reads data from the server
client.read();

// API: Checks if data is available to read
client.available();

// API: Disconnects from the server
client.stop()

// Sample Code: Simple HTTP GET Request
#include <WiFi.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

const char* host = "example.com";
const int port = 80; // Standard HTTP port

WiFiClient client;

void setup() {
  Serial.begin(115200);

  // Connect to the Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  // Connect to the remote server
  Serial.print("Connecting to ");
  Serial.print(host);
  Serial.print(":");
  Serial.println(port);

  if (client.connect(host, port)) {
    Serial.println("Connected to server!");
    // Once connected, you can send or receive data

    // Example of sending an HTTP GET request
    client.println("GET / HTTP/1.1");
    client.println("Host: example.com");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("Connection failed.");
  }
}

void loop() {
  // Handle incoming data if connected
  while (client.connected() || client.available()) {
    if (client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }
  }

  // Close the connection when the server is done responding
  if (!client.connected()) {
    Serial.println("Disconnecting.");
    client.stop();
  }
}

// Sample code: Sending Sensor Data to a Remote Server
#include <WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

const char* host = "your-server.com";
const int httpPort = 80; // HTTP port

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void loop() {
  // Read temperature and humidity from the sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor");
    return;
  }

  // Connect to the server
  if (client.connect(host, httpPort)) {
    String data = "temperature=" + String(temperature) + "&humidity=" + String(humidity);

    // Send HTTP POST request
    client.println("POST /upload HTTP/1.1");
    client.println("Host: your-server.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.println(data);

    // Read the server's response
    while (client.connected() || client.available()) {
      if (client.available()) {
        String response = client.readStringUntil('\n');
        Serial.println("Server response: " + response);
      }
    }

    // Close the connection
    client.stop();
  } else {
    Serial.println("Failed to connect to server");
  }

  // Wait before sending the next reading
  delay(60000); // 60 seconds delay
}
