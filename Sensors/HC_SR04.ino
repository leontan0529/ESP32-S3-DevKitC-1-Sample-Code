/*
Author: Leon Tan

APIs, explanations and sample code for HC-SR04 ultrasonic sensor
*/

// API: pulseIn() built-in function
long pulseIn(uint8_t pin, uint8_t value, unsigned long timeout);
/*
pin: GPIO pin number used.
value: the type of pulse to measure. (HIGH or LOW)
timeout: (optional) number of microseconds to wait for the pulse start. Default is no timeout.
return: the number of microseconds or 0 for no pulse.
*/

// Sample code using pulseIn()
#define TRIG_PIN 5
#define ECHO_PIN 18

void setup() {
  // Initialize the serial communication:
  Serial.begin(115200);
  // Configure the pins:
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Send a 10us pulse to the trigger pin. This causes the sensor to send out an ultrasonic burst.
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // Measure the duration of the echo pin's pulse in microseconds.
  long duration = pulseIn(ECHO_PIN, HIGH);
  // Calculate the distance in centimeters:
  float distance = (duration * 0.0343) / 2;
  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  // Add a delay before the next measurement
  delay(500);
}

// Sample code: pulseIn() with improved accuracy
float getDistance() {
  long sum = 0;
  //read 5 times and take average of them.
  for (int i = 0; i < 5; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.0343 / 2;
    sum += distance;
    delay(50); // Small delay between readings
  }
  return sum / 5.0; // Return the average distance
}

void loop() {
  float distance = getDistance();
  // handling out-of-range error
  if (distance > 400 || distance < 2) {
    Serial.println("Out of range");
  } else {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(1000);
}

// API: Create an instance of the NewPing class
NewPing classname(trigger_pin, echo_pin, max_distance);
/*
trigger_pin: The GPIO pin connected to the Trig pin of the ultrasonic sensor.
echo_pin: The GPIO pin connected to the Echo pin of the ultrasonic sensor.
max_distance: (Optional) The maximum distance you want to measure (in centimeters).
*/

// API: Sends a ping and returns the echo time in microseconds
unsigned int duration = sonar.ping();

// API:	Sends a ping and returns the distance in centimeters
// If the object is out of range, it returns 0
unsigned int distance = sonar.ping_cm();
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");

// API: Sends a ping and returns the distance in inches
// If the object is out of range, it returns 0
ping_in();

// API: Sends multiple pings (as specified by iterations) and returns the median distance in centimeters
// This helps in reducing noise and improving accuracy
unsigned int distance = sonar.ping_median(5);
Serial.print("Median Distance: ");
Serial.print(distance);
Serial.println(" cm");
