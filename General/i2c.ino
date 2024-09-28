/*
Author: Leon Tan

APIs, explanations and sample code for I2C (inter-integrated circuit)
*/

// API: Initializes the I2C bus as a master(default) or a slave
Wire.begin();

// API: Begins a transmission
//Start communication with the device at address 0x76
Wire.beginTransmission(0x76);

// API: Sends data
Wire.write(data);

// API: Sends the data and ends the transmission
Wire.endTransmission();

// API: Requests a specified number of bytes
//Request 2 bytes from the device at address 0x76
Wire.requestFrom(0x76, 2);

// API: Reads a byte of data
Wire.read();

// Sample code 
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  Wire.beginTransmission(0x76); // Start communication with device at address 0x76
  Wire.write(0xF7); // Write register address to read from
  Wire.endTransmission(); // End transmission
  Wire.requestFrom(0x76, 2); 
  while(Wire.available()) { // Request 2 bytes from the device
    char c = Wire.read(); // Read the bytes received
    Serial.print(c, HEX); // Print the byte data in hexadecimal
  }
  delay(1000);
}

// Sample code: interface with BMP280
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

// Create an instance of the BMP280 sensor
Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  // Initialize I2C communication
  if (!bmp.begin(0x76)) { // Address of the BMP280
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  
  Serial.println("BMP280 sensor initialized successfully.");
  }

void loop() {
  // Read temperature and pressure values
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure();

  // Display the values
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" *C");
  Serial.print("Pressure = ");

  Serial.print(pressure / 100.0F);
  Serial.println(" hPa");
  
  delay(2000); // Wait 2 seconds before the next reading
}
