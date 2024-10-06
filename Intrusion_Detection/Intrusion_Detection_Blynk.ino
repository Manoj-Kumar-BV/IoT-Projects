#define BLYNK_TEMPLATE_ID "TMPL3hcRhdNzC"
#define BLYNK_TEMPLATE_NAME "Intrusion Detection"
#define BLYNK_AUTH_TOKEN "ME3SxmtikybfJQ2uTVQeQnT8wr4CKXsC"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN;  // Replace with your Blynk authentication token

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

  // Connect to Blynk
  Blynk.begin(auth, ssid, password);
}

void readAndUploadMotionData() {
  // Read the state of the PIR sensor
  motionDetected = digitalRead(PIR_PIN);

  // Print the motion detection state to the serial monitor
  if (motionDetected) {
    Serial.println("Motion detected!");
    
    // Turn on LED if motion is detected
    digitalWrite(LED_PIN, HIGH);
    
    // Send motion detection data to Blynk app
    Blynk.virtualWrite(V1, "Motion Detected");  // V1 is a virtual pin in the Blynk app
  } else {
    Serial.println("No motion detected.");
    
    // Turn off LED if no motion is detected
    digitalWrite(LED_PIN, LOW);
    
    // Update Blynk app
    Blynk.virtualWrite(V1, "No Motion");
  }
}

void loop() {
  // Continuously run Blynk and read/upload motion detection data
  Blynk.run();
  readAndUploadMotionData();
  delay(1000);  // Check every 10 seconds (adjust delay as needed)
}
