#include <WiFi.h>
#include <FirebaseESP32.h>

// Firebase configuration
#define FIREBASE_HOST "https://forest-fire-e9b28-default-rtdb.firebaseio.com/" // Replace with your Firebase host URL
#define FIREBASE_AUTH "gfSvMfshMRij3LDTOQNL3otR7jO5nXry99c4TQHA" // Replace with your Firebase authentication token

// Define Firebase and Wi-Fi credentials
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Wi-Fi credentials
const char* ssid = "OP";      // Replace with your Wi-Fi SSID
const char* password = "12345678";  // Replace with your Wi-Fi password

// MQ-2 sensor pin
#define MQ2_PIN 34  // Analog input for gas sensor (GPIO34)

// LED pin
#define LED_PIN 5   // Define the pin for LED (GPIO5)

// Threshold for gas level to trigger fire detection
#define GAS_THRESHOLD 250

// Variable to hold gas sensor value
int gasLevel = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize pin modes
  pinMode(MQ2_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Turn off LED initially

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Firebase configuration
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Firebase.reconnectWiFi(true);
}

void readAndUploadGasData() {
  // Read gas level from MQ-2 sensor
  gasLevel = analogRead(MQ2_PIN);  // Read analog value from MQ-2 sensor

  // Print gas level to serial monitor
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  // Check if gas level exceeds threshold
  if (gasLevel > GAS_THRESHOLD) {
    // Turn on LED if fire is detected
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Fire detected! Gas level is high.");
  } else {
    // Turn off LED if no fire is detected
    digitalWrite(LED_PIN, LOW);
    Serial.println("No fire detected.");
  }

  // Send gas level data to Firebase
  Firebase.setInt(firebaseData, "/forest_fire/gas_level", gasLevel);
}

void loop() {
  // Continuously read and upload gas level data
  readAndUploadGasData();
  delay(1000);  // Check every 10 seconds (adjust delay as needed)
}
