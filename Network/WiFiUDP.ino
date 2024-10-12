/*
Author: Leon Tan

APIs, explanations and sample code for WiFiUDP library
*/

// API: Creates an instance of the WiFiUDP class
WiFiUDP udp;

// API: Initializes UDP and binds it to the specified port
udp.begin(port);

// API: Starts a new UDP packet destined for a specified remote host and port
udp.beginPacket("192.168.1.100", 1234);

// API: Writes data to the UDP packet
udp.write("Hello ESP32", 10);

// API: Marks the end of the packet and sends it
udp.endPacket();

// API: Checks if a UDP packet is available for reading and returns the size of the packet
int packetSize = udp.parsePacket();

// API: Reads incoming data from the UDP buffer
char incomingPacket[255];
udp.read(incomingPacket, 255);

// API: Gets the IP address of the sender of the received packet
IPAddress senderIP = udp.remoteIP();

// API: Gets the port number of the sender of the received packet
int senderPort = udp.remotePort();

// API: Closes the UDP connection
udp.stop();

// Sample code: Send in UDP
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";
WiFiUDP udp;

// Target IP address
IPAddress remoteIP(192, 168, 1, 100);
unsigned int remotePort = 1234; // Target port

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  udp.begin(1234); // Listening port
}

void loop() {
  udp.beginPacket(remoteIP, remotePort);
  udp.write("Hello, ESP32 UDP here!");
  udp.endPacket();
  delay(2000); // Send every 2 seconds
}

// Sample code: Receive in UDP
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";
WiFiUDP udp;
unsigned int localPort = 1234; // Listening port

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  udp.begin(localPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    char incomingPacket[255];
    int len = udp.read(incomingPacket, 255);
    if (len > 0) {
      incomingPacket[len] = '\0'; // Null-terminate
    }

    Serial.printf("Received packet: '%s'\n", incomingPacket);
    Serial.print("From IP: ");
    Serial.println(udp.remoteIP());
    Serial.print("From port: ");
    Serial.println(udp.remotePort());
  }
}

// Sample code: UDP broadcast (sending data to all devices)
#include <WiFi.h>
#include <WiFiUDP.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

WiFiUDP udp;
const int broadcastPort = 4210; // Port to broadcast on

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void loop() {
  // Get the broadcast IP address
  IPAddress broadcastIP = ~WiFi.subnetMask() | WiFi.localIP();

  // Start a UDP packet to the broadcast address
  udp.beginPacket(broadcastIP, broadcastPort);

  // Send the broadcast message
  udp.write("Hello, all devices!");

  // Finish and send the packet
  udp.endPacket();

  Serial.println("Broadcast packet sent");

  // Wait before sending the next broadcast
  delay(5000);
}
