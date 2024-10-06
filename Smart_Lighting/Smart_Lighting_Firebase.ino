#include <WiFi.h>
#include <FirebaseESP32.h>

// Firebase configuration
#define FIREBASE_HOST "https://smart-lighting-system-e63fd-default-rtdb.firebaseio.com/" // Replace with your Firebase host URL
#define FIREBASE_AUTH "qn7lgx7RkeOedlyl3h8PRyq8ZK33yCHKLZT2XGAi"               // Replace with your Firebase authentication token

// Define Firebase and Wi-Fi credentials
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Wi-Fi credentials
const char* ssid = "OP";
const char* password = "12345678";

// Define pins
#define LDR_PIN 34  // Analog pin for LDR
#define LED_PIN 2   // Digital pin for LED
#define LED_PIN2 23 // Digital pin for LED

// Threshold value to determine if it's dark or light
const int threshold = 3500;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Set LED pins as output
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Initialize LEDs as off
  digitalWrite(LED_PIN2, LOW);
  
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
  
  // Start checking and operating LEDs based on LDR
  checkLDRAndOperate();
}

void checkLDRAndOperate() {
  // Read LDR value
  int ldrValue = analogRead(LDR_PIN);
  bool ledState = (ldrValue > threshold);

  // Debugging output for LDR value
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Update LDR value in Firebase
  Firebase.setInt(firebaseData, "/smart_lighting/ldr_value", ldrValue);

  // Control LEDs based on LDR value
  if (ledState) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN2, HIGH); // Turn on LEDs if it's dark
    Firebase.setBool(firebaseData, "/smart_lighting/led_status", true); // Indicate LEDs are ON in Firebase
    Serial.println("LEDs ON (Auto)");
  } else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(LED_PIN2, LOW); // Turn off LEDs if it's bright
    Firebase.setBool(firebaseData, "/smart_lighting/led_status", false); // Indicate LEDs are OFF in Firebase
    Serial.println("LEDs OFF (Auto)");
  }
}

void loop() {
  // Continuously check the LDR value and operate LEDs
  checkLDRAndOperate();
  delay(1000); // Adjust delay as needed
}
