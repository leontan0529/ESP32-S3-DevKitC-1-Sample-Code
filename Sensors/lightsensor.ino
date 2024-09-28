/*
Author: Leon Tan

APIs, explanations and sample code for light sensor
*/

// API: Analog input
int value = analogRead(pin);
/*
Pin: the analog pin number where the sensor's analog output is connected.
Return: an integer value representing the voltage level on the pin, scaled between 0 and 4095. The ADC width is 12-bit by default. The width can be set and the attenuation level can be set.
*/

// API: Digital input
int digitalState = digitalRead(25); // Read from digital pin GPIO 25
if(digitalState == HIGH) {
  Serial.println("Light level is above the threshold");
} else {
  Serial.println("Light level is below the threshold");
}

// API: Pin configuration
pinMode(25, INPUT); 

// Sample code
const int analogPin = 34; // Analog output pin from the light sensor
const int digitalPin = 25; // Digital output pin from the light sensor

void setup() {
  Serial.begin(115200); // Initialize serial communication
  pinMode(digitalPin, INPUT); // Set digital pin as input
}

void loop() {
  // Read the analog value from the sensor
  int lightLevel = analogRead(analogPin);
  // Read the digital state from the sensor
  int digitalState = digitalRead(digitalPin);
  Serial.print("Analog Light Level: ");
  Serial.println(lightLevel); // Print the analog light level
  Serial.print("Digital Output State: ");
  Serial.println(digitalState == HIGH ? "HIGH" : "LOW"); // Print the digital state
  delay(500); // Wait for 500ms before the next loop
}
