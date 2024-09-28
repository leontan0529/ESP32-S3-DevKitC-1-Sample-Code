/*
Author: Leon Tan

Applications of pointers
*/

// Linked List
struct Node {
  int data;
  Node *next;
}

Node *head = new Node();
head->data = 1;
head->next = new Node();
head->next->data = 2;

// Passing large structures to functions
struct SensorData {
  int temperature;
  int humidity;
}

void processSensorData(SensorData *data) {
  Serial.println(data->temperature);
}

void setup() {
  SensorData data = {25, 60};//initiate the structure
  processSensorData(&data);
}

// Manipulate C-Style Strings
char str[] = "Hello";
char *ptr = str;
while(*ptr != '\0') {
  Serial.println(*ptr);
  ptr++;
}

// Initialise function pointer
void myFunction() {
  Serial.println("Hello");
}

void (*funcPtr)() = myFunction;

funcPtr(); // Calls myFunction

// Simplify declaration of function pointer
int add(int a, int b) {
  return a + b;
}

typedef int (*Operation)(int, int);

Operation op = &add; // or just = add; in C
int result = op(3, 4); // result will be 7
