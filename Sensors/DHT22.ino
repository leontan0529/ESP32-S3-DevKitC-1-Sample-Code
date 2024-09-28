/*
Author: Leon Tan

APIs, explanations and sample code for DHT22 temperature and humidity digital sensor
*/

// API: Initiate the DHT sensor
void begin();

// API: Read the relative humidity as a percentage
float readHumidity();

// API: Read the temperature in Celsius (default)
float readTemperature(bool isFahrenheit = false);

// API: Calculates the heat index based on the current temperature and humidity
float computeHeatIndex(float temperature, float humidity, bool isFahrenheit = true);

// API: Converts a temperature from Celsius to Fahrenheit
float convertCtoF(float celsius);

// API: Converts a temperature from Fahrenheit to Celsius
float convertFtoC(float fahrenheit);

// Sample Code
#include "DHT.h“ //include the library.
#define DHTPIN 4 // define the constant of the GPIO pin to use.
#define DHTTYPE DHT22 // define the type of sensor.

DHT dht(DHTPIN, DHTTYPE); // create an instance of the DHT class.

void setup() {
  Serial.begin(115200);
  dht.begin(); //initiate the sensor. Call before read the data.
}

void loop() {
  delay(2000); // wait 2 seconds.
  // Read temperature or humidity takes about 250 milliseconds.
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!"); // handle the error
    return;
  }
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");
  Serial.print("Heat Index: ");
  Serial.print(heatIndex);
  Serial.println(" *C");
}
