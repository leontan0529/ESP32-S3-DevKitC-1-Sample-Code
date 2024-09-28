/*
Author: Leon Tan

APIs, explanations and sample code for serial communications
*/

// API: Initialise serial 0
Serial.begin(baudrate, config, rxPin,txPin, bufferSize)

// API: Check if data is waiting to be read
Serial.available();

// API: Reads the next byte of incoming serial data. If no data is available, it returns -1
char incomingByte = Serial.read();

// API: Reads characters from the serial buffer into a String object until a newline character is encountered or a timeout occurs
String incomingString = Serial.readString();

// API: Reads multiple bytes
Serial.readBytes(buffer, length);

// API: Writes binary data to the serial port
Serial.write('A’);
Serial.write(myBuffer, sizeof(myBuffer));

// API: Sends text to the serial port
Serial.print(data) // ends data without a newline
Serial.println(data); // appends a newline at the end

// API: Reads characters from the serial buffer into a String until the specified character is encountered
String incomingString = Serial.readStringUntil('\n’);

// API: Waits for the transmission of outgoing serial data to complete
Serial.flush();

// Sample code
void setup() {
  Serial.begin(115200); // Start the serial communication at 115200 baud rate
}

void loop() {
  if (Serial.available() > 0) { // Check if data is available to read
    // Read the incoming data until newline character
    String inputString = Serial.readStringUntil('\n');
    // Print the received data back to the serial monitor
    Serial.print("You entered: ");
    Serial.println(inputString);
  }
}
