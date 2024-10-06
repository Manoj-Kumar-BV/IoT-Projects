#define BLYNK_TEMPLATE_ID "TMPL3ougzyvrW"
#define BLYNK_TEMPLATE_NAME "Smart Ligthing"
#define BLYNK_AUTH_TOKEN "74Lug2jwLxqlpM6mNsr9duMusq265k5H"

// Include necessary libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Define pins
#define LDR_PIN 34  // Analog pin for LDR
#define LED_PIN 2   // Digital pin for LED
#define LED_PIN2 23 // Digital pin for LED

// Threshold value to determine if it's dark or light
const int threshold = 3900;

// Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

// Your Wi-Fi credentials
char ssid[] = "OP";
char pass[] = "00000007";

BlynkTimer timer;
bool isAutoMode = true;  // Default mode is Auto

// Function to check mode and operate LEDs accordingly
void checkModeAndOperate() {
  // Read the mode from Blynk (V2)
  Blynk.syncVirtual(V2);

  if (isAutoMode) {
    // Read LDR value
    int ldrValue = analogRead(LDR_PIN);
    bool ledState = (ldrValue > threshold);

    // Debugging output for LDR value
    Serial.print("LDR Value: ");
    Serial.println(ldrValue);

    // Send LDR value to Blynk Virtual Pin V0
    Blynk.virtualWrite(V0, ldrValue);

    // Control LED based on LDR value
    if (ledState) {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(LED_PIN2, HIGH); // Turn on LED if it's dark
      Blynk.virtualWrite(V1, 1); // Update Blynk LED widget state
      Serial.println("LEDs ON (Auto)");
    } else {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(LED_PIN2, LOW); // Turn off LED if it's bright
      Blynk.virtualWrite(V1, 0); // Update Blynk LED widget state
      Serial.println("LEDs OFF (Auto)");
    }
  } else {
    // In Manual mode, read the state from V3
    Blynk.syncVirtual(V3);
  }
}

// Blynk function to handle mode change
BLYNK_WRITE(V2) {
  isAutoMode = param.asInt(); // V2 controls Auto/Manual mode
  if (isAutoMode) {
    Serial.println("Switched to Auto Mode");
  } else {
    Serial.println("Switched to Manual Mode");
  }
}

// Blynk function to handle LED control in Manual mode
BLYNK_WRITE(V3) {
  if (!isAutoMode) {
    int manualLEDState = param.asInt();
    if (manualLEDState == 1) {
      digitalWrite(LED_PIN, HIGH);
      digitalWrite(LED_PIN2, HIGH);
      Serial.println("LEDs ON (Manual)");
    } else {
      digitalWrite(LED_PIN, LOW);
      digitalWrite(LED_PIN2, LOW);
      Serial.println("LEDs OFF (Manual)");
    }
    Blynk.virtualWrite(V1, manualLEDState); // Update Blynk LED widget state
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("Starting...");

  // Set LED pins as output
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Initialize LEDs as off
  digitalWrite(LED_PIN2, LOW);
  Serial.println("LED pins initialized");

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  Blynk.begin(auth, ssid, pass);

  // Check if connected to Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Wi-Fi connected");
  } else {
    Serial.println("Wi-Fi connection failed");
  }

  // Setup a function to be called every second to check mode and operate LEDs
  timer.setInterval(1000L, checkModeAndOperate);
  Serial.println("Timer initialized, starting loop");
}

void loop() {
  Blynk.run(); // Run Blynk
  timer.run(); // Run timer
}