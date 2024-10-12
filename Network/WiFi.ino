/*
Author: Leon Tan

APIs, explanations and sample code for WiFi connection
*/

// API: Connects to a specified Wi-Fi network using the SSID and password as STA
WiFi.begin(ssid, password);

// API: Returns the current connection status
WiFi.status();
/*
WL_CONNECTED: Connected to a network.
WL_NO_SSID_AVAIL: SSID not available.
WL_CONNECT_FAILED: Connection failed.
WL_IDLE_STATUS: Idle status (not connected).
WL_DISCONNECTED: Disconnected from a network.
*/

// API: Returns the MAC address of the ESP32-S3 in WIFI_STA mode
WiFi.macAddress();

// API: Returns the IP address assigned to the ESP32-S3 by the DHCP server
WiFi.localIP();

// Sample code: Connect to WiFi
#include <WiFi.h> // Include the Wi-Fi library

const char* ssid = "YourNetworkName"; // Replace with your network SSID (name)
const char* password = "YourPassword"; // Replace with your network password

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  WiFi.begin(ssid, password); // Start Wi-Fi connection

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi network");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the IP address
}

void loop() {
  // Your main code here
}

// API: Disconnects from the current Wi-Fi network
WiFi.disconnect();

// API: Try reconnecting to the last known Wi-Fi network
WiFi.reconnect();

// API: Returns true if the ESP32 is currently connected to a Wi-Fi network
WiFi.isConnected();

// API: Sets a custom hostname for the ESP32 in STA mode
WiFi.setHostname(hostname);

// API: Start Wi-Fi STA with specified Wi-Fi channel and BSSID
WiFi.begin(ssid, password, channel, bssid);

// Sample code: Reconnecting to WiFi automatically
#include <WiFi.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

void setup() {
  Serial.begin(115200);
 
  // Begin Wi-Fi connection in Station Mode
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if the ESP32 is still connected to Wi-Fi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi connection lost. Reconnecting...");

    WiFi.disconnect();
    WiFi.reconnect();

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }

    Serial.println("\nReconnected to Wi-Fi");
  }

  delay(5000); // Check Wi-Fi status every 5 seconds
}

// API: Configures the static IP address, gateway, subnet mask, primary, and
secondary DNS servers
WiFi.config(local_ip, gateway, subnet, primaryDNS, secondaryDNS);
/*
All the parameters are IPAddress type data. The local_ip is the only compulsory parameter. The rest, if not provided, will be obtained via DHCP.
local_ip: The static IP address you want to assign to the ESP32.
gateway: (Optional) The IP address of the network gateway (usually your router).
subnet: (Optional)The subnet mask (usually 255.255.255.0 for most home networks).
primaryDNS:(Optional)The primary DNS server (the IP address used to resolve domain names).
secondaryDNS:(Optional)The secondary DNS server (used if the primary fails).
*/

// Sample code: Setting a Static IP Address
#include <WiFi.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

// Define a static IP address, gateway, and subnet
IPAddress local_IP(192, 168, 1, 184); // Change to your preferred static IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);

  // Configure the ESP32 to use a static IP
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Failed to configure static IP");
  }

  // Begin Wi-Fi connection in Station Mode
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the ESP32's static IP address
}

void loop() {
  // Put your main code here, to run repeatedly:
  }

// API: Returns the Received Signal Strength Indicator (RSSI) of the connected network
WiFi.RSSI();

// API: Sets the mode of the Wi-Fi and getting the current Wi-Fi mode
WiFi.mode(WIFI_STA);
/*
WIFI_STA: Station mode, which is used to connect the ESP32 to an existing Wi-Fi network as a client.
WIFI_AP: Access point mode, where the ESP32 creates its own network and allows other devices to connect to it.
WIFI_AP_STA: Both station and access point mode. The ESP32 can connect to an existing network and create its own network simultaneously.
WIFI_OFF: Turns off the Wi-Fi interface.
*/

// Sample code: Set up as STA then AP mode
#include <WiFi.h>
// Wi-Fi credentials for Station mode (client)
const char* ssid_STA = "Your_SSID";
const char* password_STA = "Your_PASSWORD";

// Wi-Fi credentials for Access Point (AP) mode
const char* ssid_AP = "ESP32_AP"; // SSID of the AP you create
const char* password_AP = "12345678"; // Password of the AP

void setup() {
  Serial.begin(115200);

  // Set the ESP32-S3 to dual-mode: Access Point (AP) and Station (STA)
  WiFi.mode(WIFI_AP_STA);

  // Start Station (STA) and attempt to connect to the Wi-Fi network
  WiFi.begin(ssid_STA, password_STA);
  Serial.println("Connecting to WiFi (Station mode)...");

  // Wait until connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to Wi-Fi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // Set up the Access Point (AP)
  WiFi.softAP(ssid_AP, password_AP);
  Serial.println("Access Point (AP) started");

  // Get the IP address of the AP
  IPAddress IP_AP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP_AP);
}

void loop() {
  // In the loop, you can add any functionality or checks for clients
  //connected to the AP
}

// API: Creates a Wi-Fi network with a given SSID (name) and password (open network if no password)
WiFi.softAP(ssid, password);

// API: Returns the MAC address of the ESP32-S3 in WIFI_AP mode
WiFi.softAPmacAddress();

// API: Returns the IP address of the ESP32 as the access point
WiFi.softAPIP();

// API: Configures the IP address, gateway, and subnet for the access point
WiFi.softAPConfig(local_ip, gateway, subnet);

// API: Returns the int number of devices (stations) currently connected to the access point
WiFi.softAPgetStationNum();

// API: Disconnects all connected stations from the access point
WiFi.softAPdisconnect();

// API: Set the channel, hide the SSID, and specify the maximum number of connections
WiFi.softAP(ssid, password, channel, ssid_hidden, max_connection);
/*
ssid: AP network ID.
password: password of the AP.
channel: Wi-Fi channel used (int type).
ssid_hidden: Boolean type
max_connection: integer type.
*/

// Sample code: Set custom IP and multiple connections
#include <WiFi.h>
#include <WebServer.h>

// Set the SSID and password for the access point
const char* ssid = "Custom_AP";
const char* password = "mypassword";

// Custom IP settings
IPAddress local_ip(192, 168, 10, 1);
IPAddress gateway(192, 168, 10, 1);
IPAddress subnet(255, 255, 255, 0);

// Create a web server object
WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Configure the access point with a custom IP
  WiFi.softAPConfig(local_ip, gateway, subnet);

  // Start the Wi-Fi access point
  WiFi.softAP(ssid, password, 6, 0, 8); // 8 clients max, channel 6, visible SSID

  // Print the custom IP address of the access point
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP: ");
  Serial.println(IP);

  // Set up a route for the root URL
  server.on("/", []() {
    server.send(200, "text/html", "<h1>ESP32 Access Point with Custom IP</h1>");
  });

  // Start the web server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}

// Sample code: Monitoring connected device
#include <WiFi.h>

const char* ssid = "Monitor_AP";
const char* password = "password123";

void setup() {
  Serial.begin(115200);

  // Start the Wi-Fi access point
  WiFi.softAP(ssid, password);

  // Print the IP address of the access point
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point IP: ");
  Serial.println(IP);
}

void loop() {
  // Print the number of connected clients
  int numStations = WiFi.softAPgetStationNum();
  Serial.print("Connected devices: ");
  Serial.println(numStations);

  // Wait for 5 seconds before checking again
  delay(5000);
}
