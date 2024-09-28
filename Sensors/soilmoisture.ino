/*
Author: Leon Tan

APIs, explanations and sample code for soil moisture sensor
*/

// API: Read analog
analogRead(sensorPin)
/*
1. Reads the analog voltage from the soil moisture sensor.
2. The ESP32-S3’s ADC returns a value between 0 (0V) and 4095 (3.3V) based on the moisture content since it has a 12-bit ADC resolution.
3. Calibrate the sensor for a specific soil and environment by measuring the values in fully dry (0) and fully saturated soil (4095).
4. Map these raw ADC values to a percentage moisture for easier interpretation.
*/

// API: Mapping values of different ranges
map(value, fromLow, fromHigh, toLow, toHigh)
/*
An analog sensor that gives values from 0 to 1023, but you want to map these values to a range of 0 to 100.
*/

// API: Limit a value to a specific range
// ensure value stays within 0 to 100
int value = 150;
// constrainedValue will be 100
int constrainedValue = constrain(value, 0, 100);

// Sample code:
// Define pins
const int moisturePin = 36; // Analog pin connected to sensor OUT
const int disablePin = 4; // GPIO pin to control sensor power

void setup() {
  Serial.begin(115200); // Start the serial communication
  pinMode(disablePin, OUTPUT);
  digitalWrite(disablePin, HIGH); // Disable the sensor by setting the disable pin HIGH
}

void loop() {
  // Enable the sensor
  digitalWrite(disablePin, LOW); // Enable the sensor by pulling the disable pin LOW
  delay(500); // Wait for sensor to stabilize
  // Read the moisture value
  int sensorValue = analogRead(moisturePin);
  // Print the moisture value
  Serial.print("Soil Moisture Value: ");
  Serial.println(sensorValue);
  // Disable the sensor to save power
  digitalWrite(disablePin, HIGH); // Disable the sensor by pulling the disable pin HIGH
  // Wait before next reading
  delay(10000); // Adjust delay as needed
}

// Sample code 2
const int moisturePin = 36; // Analog pin connected to sensor OUT
const int disablePin = 4; // GPIO pin to control sensor power

// Define the range for dry and wet soil (calibration)
const int dryValue = 3500; // Example value for dry soil
const int wetValue = 1500; // Example value for wet soil

void setup() {
  Serial.begin(115200);
  pinMode(disablePin, OUTPUT);
  digitalWrite(disablePin, HIGH); // Disable the sensor by setting the disable pin HIGH
}

void loop() {
  digitalWrite(disablePin, LOW); // Enable the sensor by pulling the disable pin LOW
  delay(500); // Wait for sensor to stabilize
  
  int sensorValue = analogRead(sensorPin);
  
  // Map the sensor value to a percentage (0% - 100%)
  int moisturePercent = map(sensorValue, dryValue, wetValue, 0, 100);

  // Constrain the value to 0-100% range
  moisturePercent = constrain(moisturePercent, 0, 100);

  Serial.print("Soil Moisture Level: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Disable the sensor to save power
  digitalWrite(disablePin, HIGH);
  
  delay(1000);
}
