#define BLYNK_TEMPLATE_ID "TMPL3jYkIxT7U"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#define BLYNK_AUTH_TOKEN "qj0hNtYsXUAOlwZZSlUpK89YGH_pMMxz"

#include <WiFi.h>
#include <FirebaseESP32.h>
#include <BlynkSimpleEsp32.h>  // Include Blynk library

// Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;


// Wi-Fi credentials
const char* ssid = "OP";      // Replace with your Wi-Fi SSID
const char* password = "12345678";  // Replace with your Wi-Fi password

// Define IR sensor pins
#define IR_SENSOR_SLOT1 34  // Digital pin for IR sensor 1 (Slot 1)
#define IR_SENSOR_SLOT2 35  // Digital pin for IR sensor 2 (Slot 2)

// Define parking slot status
String slot1Status = "Available";  // Initialize slot 1 as Available
String slot2Status = "Available";  // Initialize slot 2 as Available

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set IR sensor pins as input
  pinMode(IR_SENSOR_SLOT1, INPUT);
  pinMode(IR_SENSOR_SLOT2, INPUT);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Initialize Blynk
  Blynk.begin(auth, ssid, password);
}

void checkParkingStatus() {
  // Check slot 1 status
  if (digitalRead(IR_SENSOR_SLOT1) == LOW) {  // LOW means object detected (car in slot)
    slot1Status = "Occupied";
  } else {
    slot1Status = "Available";
  }
  Serial.print("Slot 1: ");
  Serial.println(slot1Status);

  // Update Blynk for slot 1
  Blynk.virtualWrite(V1, slot1Status); // Send status to Blynk virtual pin V1

  // Check slot 2 status
  if (digitalRead(IR_SENSOR_SLOT2) == LOW) {  // LOW means object detected (car in slot)
    slot2Status = "Occupied";
  } else {
    slot2Status = "Available";
  }
  Serial.print("Slot 2: ");
  Serial.println(slot2Status);

  // Update Blynk for slot 2
  Blynk.virtualWrite(V2, slot2Status); // Send status to Blynk virtual pin V2
}

void loop() {
  // Continuously check parking slot status
  checkParkingStatus();
  delay(2000); // Check every 2 seconds (adjust delay as needed)

  // Blynk routine
  Blynk.run();
}
