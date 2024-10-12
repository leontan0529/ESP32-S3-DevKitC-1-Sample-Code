/*
Author: Leon Tan

APIs, explanations and sample code for WiFiServer library
*/

// API: Creates an instance of the WiFiServer class that listens for incoming
connections on the specified port
WiFiServer server(port);

// API: Starts the server and listen to the incoming connections
void server.begin();

// API: Checks if a client is trying to connect
server.available();
/*
It returns a WiFiClient object for communication or an empty object if no client is connected.
*/

// API: Checks whether the client is still connected
client.connected();

// API: Stops the server from listening
void server.stop();

// API: Sends data to the connected client
client.write(data);
client.print(data);
client.println(data);

// API: Receives data from the client
client.read();
client.readStringUntil();

// Sample code: Simple Wi-Fi Web Server
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Create a WiFiServer object on port 80 (HTTP)
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the server
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client connected");

    // Wait until the client sends some data
    while (client.connected() && !client.available()) {
      delay(1);
    }

    // Read the request from the client
    String request = client.readStringUntil('\r');
    Serial.println("Received request: " + request);

    // Prepare the response
    String response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/html\r\n\r\n";
    response += "<html><body><h1>Hello from ESP32!</h1></body></html>";

    // Send the response to the client
    client.print(response);

    // Close the connection
    client.stop();
  } 
}

// Sample code: Control an LED via Wi-Fi Web Server
#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

WiFiServer server(80);

// Define the pin for LED
const int ledPin = 2;

void setup() {
  Serial.begin(115200);

  // Set up the LED pin
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // Check the request to turn the LED on or off
    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(ledPin, HIGH); // Turn LED on
    } else if (request.indexOf("/LED=OFF") != -1) {
      digitalWrite(ledPin, LOW); // Turn LED off
    }

    // Prepare the response
    String response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/html\r\n\r\n";
    response += "<html><body>";
    response += "<h1>ESP32 LED Control</h1>";
    response += "<p><a href=\"/LED=ON\">Turn LED ON</a></p>";
    response += "<p><a href=\"/LED=OFF\">Turn LED OFF</a></p>";
    response += "</body></html>";

    // Send the response
    client.print(response);

    // Close the connection
    client.stop();
  }
}

// Sample code: Real-Time Sensor Data Server
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

DHT dht(DHTPIN, DHTTYPE);

// Create a web server on port 80
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");

  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check for a client connection
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client Connected");
    client.readStringUntil('\r'); // Read the request
    client.flush();
   
    // Get temperature and humidity
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Send an HTML response with sensor data
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<html><body>");
    client.println("<h1>ESP32 Sensor Data</h1>");
    client.print("<p>Temperature: ");
    client.print(temperature);
    client.println(" &#8451;</p>");
    client.print("<p>Humidity: ");
    client.print(humidity);
    client.println(" %</p>");
    client.println("</body></html>");
    client.println();

    // Close the connection
    client.stop();
    Serial.println("Client disconnected");
  }
}
