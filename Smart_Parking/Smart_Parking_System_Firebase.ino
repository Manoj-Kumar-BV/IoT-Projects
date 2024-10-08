#include <WiFi.h>
#include <FirebaseESP32.h>

// Firebase configuration
#define FIREBASE_HOST "https://smart-parking-system-c4c74-default-rtdb.firebaseio.com/" // Replace with your Firebase host URL
#define FIREBASE_AUTH "7iIkR7x38sT4kohZawF6dO9Eh4aGAU81XSrwhjG7"                   // Replace with your Firebase authentication token

// Define Firebase and Wi-Fi credentials
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Wi-Fi credentials
const char* ssid = "OP";      // Replace with your Wi-Fi SSID
const char* password = "12345678";  // Replace with your Wi-Fi password

// Define IR sensor pins
#define IR_SENSOR_SLOT1 34  // Digital pin for IR sensor 1 (Slot 1)
#define IR_SENSOR_SLOT2 35  // Digital pin for IR sensor 2 (Slot 2)

// Define built-in LED pin
#define BUILTIN_LED 2       // Built-in LED pin (GPIO 2)

// Define parking slot status
String slot1Status = "Available";  // Initialize slot 1 as Available
String slot2Status = "Available";  // Initialize slot 2 as Available

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set IR sensor pins as input
  pinMode(IR_SENSOR_SLOT1, INPUT);
  pinMode(IR_SENSOR_SLOT2, INPUT);

  // Set built-in LED pin as output
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW); // Initially turn off the LED

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    digitalWrite(BUILTIN_LED, LOW); // LED off while not connected
  }

  Serial.println("Connected to WiFi");
  digitalWrite(BUILTIN_LED, HIGH); // Turn on LED when connected

  // Firebase configuration
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Firebase.reconnectWiFi(true);
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

  // Check slot 2 status
  if (digitalRead(IR_SENSOR_SLOT2) == LOW) {  // LOW means object detected (car in slot)
    slot2Status = "Occupied";
  } else {
    slot2Status = "Available";
  }
  Serial.print("Slot 2: ");
  Serial.println(slot2Status);

  // Update Firebase with slot statuses
  Firebase.setString(firebaseData, "/parking/slot1_status", slot1Status);
  Firebase.setString(firebaseData, "/parking/slot2_status", slot2Status);
}

void loop() {
  // Continuously check parking slot status
  checkParkingStatus();

  // Check Wi-Fi status and control LED accordingly
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn on LED if connected
  } else {
    digitalWrite(BUILTIN_LED, LOW);   // Turn off LED if not connected
  }

  delay(2000); // Check every 2 seconds (adjust delay as needed)
}
