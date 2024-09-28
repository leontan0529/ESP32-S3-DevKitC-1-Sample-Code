/*
Author: Leon Tan

APIs, explanations and sample code for relay module
*/

// API: Configures a specified pin to behave either as an input or an output
pinMode(RELAY1_PIN, OUTPUT); // Set the relay control pin as an output

// API: Sets the output level of a digital pin to HIGH (5V or 3.3V) or LOW (0V)
digitalWrite(RELAY1_PIN, LOW); // Activate the relay (if low-level triggered)

// API: Reads the value from a specified digital pin, returning HIGH or LOW
int state = digitalRead(RELAY1_PIN); // Read the current state of the relay control pin

/*Time Functions*/
// API: Pauses the program for a specified number of milliseconds
delay(1000); // Wait for 1 second

// API: Returns the number of milliseconds since the program started running. Useful for non-blocking timing control
unsigned long currentMillis = millis();

// Sample code: Example that turns a relay on and off every second
#define RELAY1_PIN 4 // GPIO pin connected to IN1
#define RELAY2_PIN 5 // GPIO pin connected to IN2

void setup() {
  // Initialize the relay control pins as outputs
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  // Set initial state for relays (usually HIGH to keep them off if low-level trigger)
  digitalWrite(RELAY1_PIN, HIGH);
  digitalWrite(RELAY2_PIN, HIGH);
}

void loop() {
  // Activate Relay 1 (turn on the device connected to Relay 1)
  digitalWrite(RELAY1_PIN, LOW); // LOW to activate if it's a low-level trigger
  delay(1000); // Keep it on for 1 second
  // Deactivate Relay 1 and activate Relay 2
  digitalWrite(RELAY1_PIN, HIGH); // HIGH to deactivate
  digitalWrite(RELAY2_PIN, LOW); // LOW to activate Relay 2
  delay(1000); // Keep it on for 1 second
  // Deactivate Relay 2
  digitalWrite(RELAY2_PIN, HIGH); // HIGH to deactivate Relay 2
  delay(1000); // Wait 1 second before looping again
}

// Sample code: Toggle the relay state by a push button with btn debouncing
const int buttonPin = 2; // The number of the pushbutton pin
const int relayPin = 4; // The number of the relay control pin

int buttonState; // The current reading from the input pin
int lastButtonState = LOW; // The previous reading from the input pin

unsigned long lastDebounceTime = 0; // The last time the output pin was toggled
unsigned long debounceDelay = 50; // The debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(relayPin, OUTPUT);
}

void loop() {
  int reading = digitalRead(buttonPin);
  // button debounce
  if (reading != lastButtonState) { // check if there is btn state change.
    lastDebounceTime = millis(); // record the time to start debounce if a btn change is detected.
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading; // update the btn state.
      if (buttonState == HIGH) {
        digitalWrite(relayPin, !digitalRead(relayPin)); // toggle the relay state.
      }
    }
  }
  lastButtonState = reading;
}

// Sample code: Basic Web Server to Control Relay
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

AsyncWebServer server(80);

#define RELAY_PIN 4

void setup(){
  Serial.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Since active is LOW, we will set as high first
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello, Relay!");
  });

  server.on("/relay_on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(RELAY_PIN, LOW);
    request->send(200, "text/plain", "Relay ON");
  });

  server.on("/relay_off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(RELAY_PIN, HIGH);
    request->send(200, "text/plain", "Relay OFF");
  });
  
  server.begin();
}

void loop(){}
