/*
Author: Leon Tan

APIs, explanations and sample code for HTTP
*/

// Sample code: GET Request 
#include<WiFi.h>
#include<HTTPClient.h>

constchar* ssid= "your-SSID";
constchar* password = "your-PASSWORD";

voidsetup() {
  Serial.begin(115200); 
 
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(1000); 
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi"); 

  if(WiFi.status() == WL_CONNECTED) {
    HTTPClienthttp;

    // Specify the URL (example: weather API)
    Stringurl= "http://jsonplaceholder.typicode.com/posts/1";
    http.begin(url);

    // Send the GET request
    int httpResponseCode= http.GET();

    // Check if the request was successful
    if(httpResponseCode> 0) {
      Stringresponse = http.getString();
      Serial.println("Response:");
      Serial.println(response);
    } else{
      Serial.printf("Error: %d\n", httpResponseCode);
  }
  
  // End the connection
  http.end();
}

void loop() {
  // Nothing here
}

// Sample code: POST Request
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Specify the URL (example: API endpoint)
    String url = "http://jsonplaceholder.typicode.com/posts";
    http.begin(url);

    // Specify content type header
    http.addHeader("Content-Type", "application/json");

    // JSON payload
    String jsonPayload = "{\"title\":\"foo\",\"body\":\"bar\",\"userId\":1}";

    // Send POST request
    int httpResponseCode = http.POST(jsonPayload);

    // Check if the request was successful
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response:");
      Serial.println(response);
    } else {
      Serial.printf("Error: %d\n", httpResponseCode);
    }

    // End the connection
    http.end();
  }
}

void loop() {
  // Nothing here
}

// Sample code: PUT Request
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Specify the URL to update the resource
    String url = "http://jsonplaceholder.typicode.com/posts/1";
    http.begin(url);

    // Specify content type header
    http.addHeader("Content-Type", "application/json");

    // JSON payload
    String jsonPayload = "{\"title\":\"updated title\",\"body\":\"updated body\",\"userId\":1}";

    // Send PUT request
    int httpResponseCode = http.PUT(jsonPayload);

    // Check if the request was successful
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response:");
      Serial.println(response);
    } else {
      Serial.printf("Error: %d\n", httpResponseCode);
    }

    // End the connection
    http.end();
  }
}

void loop() {
  // Nothing here
}

// Sample code: PATCH Request
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Specify the URL
    String url = "http://jsonplaceholder.typicode.com/posts/1";
    http.begin(url);

    // Specify content type header
    http.addHeader("Content-Type", "application/json");

    // JSON payload (only update the title)
    String jsonPayload = "{\"title\":\"partially updated title\"}";

    // Send PATCH request
    int httpResponseCode = http.PATCH(jsonPayload);

    // Check if the request was successful
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response:");
      Serial.println(response);
    } else {
      Serial.printf("Error: %d\n", httpResponseCode);
    }

    // End the connection
    http.end();
  }
}

void loop() {
  // Nothing here
}

// Sample code: DELTE Request
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your-SSID";
const char* password = "your-PASSWORD";

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Specify the URL to delete the resource
    String url = "http://jsonplaceholder.typicode.com/posts/1";
    http.begin(url);

    // Send DELETE request
    int httpResponseCode = http.sendRequest("DELETE");

    // Check if the request was successful
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Response:");
      Serial.println(response);
    } else {
      Serial.printf("Error: %d\n", httpResponseCode);
    }

    // End the connection
    http.end();
  }
}

void loop() {
  // Nothing here
}

// API: Initializes the connection to a specified URL
http.begin("http://example.com/api");

// API: Initializes a secure connection (HTTPS) to a specified URL, using a root certificate for SSL verification
http.begin("https://example.com", root_ca);

// API: Adds custom headers to the HTTP request
http.addHeader("Content-Type", "application/json");

// API: Sends an HTTP GET request
int httpCode = http.GET();

// API: Sends an HTTP POST request with a body payload
int httpCode = http.POST("{\"key\":\"value\"}");

// API: Sends an HTTP PUT request with a body payload
int httpCode = http.PUT("{\"key\":\"value\"}"); 

//API Sends an HTTP DELETE request
int httpCode = http.DELETE();

//API: Returns the response body as a string
String payload = http.getString();

//API: Returns the response body as a stream, useful for large files
Stream& response = http.getStream();

//API: Returns the size of the response payload
int len = http.getSize();

//API: Converts an HTTP error code into a humanreadable string
Serial.println(http.errorToString(httpCode));

//API: Ends the HTTP connection, freeing resources
http.end();

// Sample code: HTTP GET Request for Secure Connection
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

// Root CA for the server's SSL certificate (example for jsonplaceholder.typicode.com)
const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDdzCCAl+gAwIBAgIEbdsIrzANBgkqhkiG9w0BAQsFADBoMQswCQYDVQQGEwJV\n" \
...
"-----END CERTIFICATE-----";

const char* serverName = "https://jsonplaceholder.typicode.com/posts/1"; // Example HTTPS API

void setup() {
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  WiFiClientSecure client;

  // Use root certificate to verify SSL connection
  client.setCACert(root_ca);
  HTTPClient http;
 
  // Specify the URL
  http.begin(client, serverName);

  // Send HTTP GET request
  int httpCode = http.GET();

  // Check if the request was successful
  if (httpCode > 0) {
   String payload = http.getString();
   Serial.println("Response code: " + String(httpCode));
   Serial.println("Response: " + payload);
  } else {
   Serial.println("Error on HTTPS request");
  }

  http.end(); // Close connection
}

void loop() {
  // Nothing here
}
