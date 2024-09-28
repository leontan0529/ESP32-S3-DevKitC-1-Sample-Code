/*
Author: Leon Tan

APIs, explanations and sample code for SPIFFS
*/

// API: Initializes the SPIFFS file system
SPIFFS.begin(bool formatOnFail);

// API: Opens a file
SPIFFS.open(const char* path, const char* mode);

// API: Checks if a file exists
SPIFFS.exists(const char* path);

// API: Removes (deletes) a file
SPIFFS.remove(const char* path);

// API: Formats the SPIFFS file system
SPIFFS.format();

// API: Checks if there are more bytes available for reading
File file = SPIFFS.open("/example.txt", FILE_READ);
while (file.available()) {
  Serial.write(file.read()); // Read file byte by byte
}
file.close();

// API: Moves the file pointer to the specified offset
File file = SPIFFS.open("/example.txt", FILE_READ);
file.seek(10, SeekSet); // Move to the 10th byte in the file
Serial.println(file.read()); // Read from the 10th byte
file.close();

// Sample code: basic file I/O operations
// Writing a string to a file
File file = SPIFFS.open("/example.txt", FILE_WRITE);
if (file) {
  file.println("Hello, SPIFFS!");
  file.close();
}

// Reading a file as a string
file = SPIFFS.open("/example.txt", FILE_READ);
if (file) {
  String content = file.readString();
  Serial.println(content); // Prints: Hello, SPIFFS!
  file.close();
}

// Sample code: reading and writing WiFi credentials
#include "SPIFFS.h"

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Writing Wi-Fi credentials
  File file = SPIFFS.open("/wifi.txt", FILE_WRITE);
  if (file) {
    file.println("SSID: MyWiFi");
    file.println("Password: MyPassword");
    file.close();
    Serial.println("Wi-Fi credentials saved");
  }

  // Reading Wi-Fi credentials
  file = SPIFFS.open("/wifi.txt", FILE_READ);
  if (file) {
    Serial.println("Reading Wi-Fi credentials:");
    while (file.available()) {
      Serial.write(file.read());
    }
    file.close();
  }
}

void loop() {
  // Empty
}

// Sample code: logging
#include "SPIFFS.h"

void setup() {
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  
  // Simulating sensor data
  int sensorValue = 42;

  // Logging data
  File logFile = SPIFFS.open("/log.txt", FILE_APPEND);
  if (logFile) {
    logFile.print("Sensor value: ");
    logFile.println(sensorValue);
    logFile.close();
    Serial.println("Data logged");
  }
}

void loop() {
  // Empty
}
