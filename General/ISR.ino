/*
Author: Leon Tan

Interrupt Service Routine (ISR)
– A function that executes when an interrupt occurs.
– Short and efficient.
*/

// ISR function
void IRAM_ATTR ISR() {
  // Code to execute
}

// Debouncing of mechanical buttons with interrupts
void IRAM_ATTR handleButtonPress() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200) {
    buttonPressed = !buttonPressed;
  }
  lastInterruptTime = interruptTime;
}

// Timer interrupts
hw_timer_t *timer = NULL;

void IRAM_ATTR onTimer() {
  // Timer ISR code
}

void setup() {
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}


