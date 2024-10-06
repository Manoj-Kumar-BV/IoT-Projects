#include <WiFi.h>
#include <FirebaseESP32.h>

// Firebase configuration
#define FIREBASE_HOST "https://intrusion-detection-71946-default-rtdb.firebaseio.com/" // Replace with your Firebase host URL
#define FIREBASE_AUTH "yEgGEffsHWZPcqZR6SBre6sSEYVZaSB8PIhLsjPj" // Replace with your Firebase authentication token

// Define Firebase and Wi-Fi credentials
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Wi-Fi credentials
const char* ssid = "OP";      // Replace with your Wi-Fi SSID
const char* password = "12345678";  // Replace with your Wi-Fi password

// PIR sensor pin
#define PIR_PIN 34   // Digital input for PIR sensor (GPIO34)

// LED pin
#define LED_PIN 5    // Define the pin for LED (GPIO5)

// Variable to hold the state of motion detection
bool motionDetected = false;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize pin modes
  pinMode(PIR_PIN, INPUT);
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

void readAndUploadMotionData() {
  // Read the state of the PIR sensor
  motionDetected = digitalRead(PIR_PIN);

  // Print the motion detection state to the serial monitor
  if (motionDetected) {
    Serial.println("Motion detected!");
    
    // Turn on LED if motion is detected
    digitalWrite(LED_PIN, HIGH);
    
    // Send motion detection data to Firebase
    Firebase.setString(firebaseData, "/intrusion_detection/status", "Motion Detected");
  } else {
    Serial.println("No motion detected.");
    
    // Turn off LED if no motion is detected
    digitalWrite(LED_PIN, LOW);
    
    // Update Firebase
    Firebase.setString(firebaseData, "/intrusion_detection/status", "No Motion");
  }
}

void loop() {
  // Continuously read and upload motion detection data
  readAndUploadMotionData();
  delay(10000);  // Check every second (adjust delay as needed)
}
