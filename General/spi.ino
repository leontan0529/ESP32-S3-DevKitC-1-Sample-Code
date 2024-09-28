/*
Author: Leon Tan

APIs, explanations and sample code for serial peripheral interface (SPI)
*/

// API: Initializes the SPI bus
SPI.begin(SCK, MISO, MOSI, SS);

// API: Configures the SPI parameters for a transaction
SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); // 1 MHz, MSB first, Mode 0

// API: Transfers a byte of data to the SPI device and simultaneously receives a byte of data from the SPI device
// Send 0x42 and receive a response
uint8_t response = SPI.transfer(0x42);

// API: Transfers multiple bytes of data to the SPI device and stores the response in a buffer
uint8_t data[2] = {0x01, 0x02};
SPI.transfer(data, sizeof(data)); // Send two bytes

// API: Ends the current SPI transaction
SPI.endTransaction();

// API: Disables the SPI bus
SPI.end()

// API: For configuring SPI transactions
SPISettings(clock, bitOrder, dataMode);

// Sample code
#include <SPI.h>

const int CS_PIN = 5; // Chip select pin

void setup() {
  Serial.begin(115200);
  SPI.begin(18, 19, 23, CS_PIN); // Initialize SPI with custom pins
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Set CS high
}

void loop() {
  digitalWrite(CS_PIN, LOW); // Select the SPI device
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0)); // 1 MHz, MSB first, Mode 0
  uint8_t response = SPI.transfer(0x42); // Send data and receive a response
  SPI.endTransaction();
  digitalWrite(CS_PIN, HIGH); // Deselect the SPI device
  Serial.print("Response: ");
  Serial.println(response, HEX);
  delay(1000); // Wait for a second
}

// Sample code: interface with an SD card to log data
#include <SPI.h>
#include <SD.h>

const int chipSelect = 5; // CS pin for SD card module

void setup() {
  Serial.begin(115200);
  // Initialize SPI communication with SD card
  if (!SD.begin(chipSelect)) { // Initializes the SD card for communication using the specified chip select pin.
  Serial.println("SD card initialization failed!");
  return;
  }

  Serial.println("SD card initialized successfully.");

  // Create or open a file on the SD card
  File dataFile = SD.open("datalog.txt", FILE_WRITE); // Opens a file on the SD card.

  // If the file opened successfully, write to it
  if (dataFile) {
    dataFile.println("Hello, this is a test log."); // Writes data to the file.
    dataFile.close(); // Closes the file to ensure data is properly saved.
    Serial.println("Data written to file.");
  } else {
    // If the file didn't open, print an error
    Serial.println("Error opening datalog.txt");
  }
}

void loop() {
  // Nothing needed in the loop for this basic example
}
