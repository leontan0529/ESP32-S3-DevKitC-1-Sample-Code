/*
Author: Leon Tan

Examples of callback functions
*/
// Handle asynchronous events
void callback() {
  Serial.println("Callback function called");
}

void registerCallback(void (*func)()) {
  func();
}

void setup() {
  registerCallback(callback);
}

// Handle timer interrupts
void onTimer() {
  Serial.println("Timer interrupt");
}

hw_timer_t *timer = NULL;

void setup() {
  Serial.begin(115200);
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

// Implement a state machine
void state1() {
  Serial.println("State 1");
}

void state2() {
  Serial.println("State 2");
}

void (*state)() = state1;

void setup() {
  Serial.begin(115200);
}

void loop() {
  state();
  delay(1000);
  state = (state == state1) ? state2 : state1;
}

// Handling network communication
void onReceive(char* data) {
  Serial.print("Received: ");
  Serial.println(data);
}

void setup() {
  Serial.begin(115200);
  // Assume WiFi or Ethernet setup
  attachNetworkCallback(onReceive);
}

// Custom serial protocol handling
void onSerialDataReceived(String data) {
  Serial.print("Received data: ");
  Serial.println(data);
}

void attachSerialCallback(void (*callback)(String)) {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    callback(data);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000); // Give some time for the Serial Monitor to start
  Serial.println("Serial Callback Example");
}

void loop() {
  // Attach the callback function for serial data reception
  attachSerialCallback(onSerialDataReceived);
}
