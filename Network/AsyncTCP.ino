/*
Author: Leon Tan

APIs, explanations and sample code for AsyncTCP library.
*/

// API for client
// API: AsyncClient class
AsyncClient *client = AsyncClient();

// API:  Connects to a TCP server using the provided IP address and port
client->connect(IPAddress(192, 168, 1, 100), 1234);

// API: Callback function for when the client successfully connects to the server
onConnect(AcConnectHandler);

// API: Callback function that is triggered when the client disconnects from the server
onDisconnect(AcConnectHandler);

// API: Callback for when data is received from the server
onData(AcDataHandler);

// API: Sends data to the connected server
const char* message = "Hello, server!";
client->write((uint8_t*)message, strlen(message));

// API: Closes the connection
client->close();

// API: Callback function to handle errors (e.g. connection failures)
client->onError([](void *arg, AsyncClient *client, err_t error) {
  Serial.printf("Error: %s\n", lwip_strerr(error));
});

// API for server
// API: Creates a TCP server on the specified port
AsyncServer *server = new AsyncServer(1234);

// API: Starts the TCP server
server->begin();

// API: Callback for when a new client connects to the server
onClient(AcConnectHandler);

// API: Handles timeout of TCP connections if server is unable to respond within a given time
onTimeout(AcTimeoutHandler);

// API: Callback for when data is received from the server
onData(AcDataHandler);

// Sample code: Connects to a remote TCP server and sends periodic messages to the server
#include <WiFi.h>
#include <AsyncTCP.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

AsyncClient *client = new AsyncClient();

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Connect to the TCP server
  client->onConnect([](void *arg, AsyncClient *client) {
    Serial.println("Connected to server!");
    client->write("Hello from ESP32!");
  });

  client->onData([](void *arg, AsyncClient *client, void *data, size_t len) {
    Serial.print("Received data: ");
    Serial.write((char*)data, len);
  });

  client->onDisconnect([](void *arg, AsyncClient *client) {
    Serial.println("Disconnected from server!");
  });

  client->connect(IPAddress(192, 168, 1, 100), 1234); // Connect to TCP server
}

void loop() {
  // No need to implement anything here, the client is fully async
}

// Sample code: TCP server listens for incoming connections
#include <WiFi.h>
#include <AsyncTCP.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

AsyncServer *server = new AsyncServer(1234); // Create server on port 1234

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Connect to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  
  // Start the TCP server
  server->onClient([](void *arg, AsyncClient *client) {
    Serial.println("New client connected!");

    client->onData([](void *arg, AsyncClient *client, void *data, size_t len) {
      Serial.print("Received data: ");
      Serial.write((char*)data, len);

      // Send response back to the client
      client->write("Hello from ESP32 server!");
    });
 
    client->onDisconnect([](void *arg, AsyncClient *client) {
      Serial.println("Client disconnected");
    });
  });
  
  server->begin();
}

void loop() {
  // The server runs asynchronously.
}
