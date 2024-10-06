#define BLYNK_TEMPLATE_ID "TMPL3S4dCPWHm"
#define BLYNK_TEMPLATE_NAME "Forest Fire"
#define BLYNK_AUTH_TOKEN "O8bNADYZkRyiPLtQt3q1kpPxmitgDr_r"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Blynk credentials
char auth[] = BLYNK_AUTH_TOKEN;  // Replace with your Blynk Auth Token

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

  // Connect to Blynk
  Blynk.begin(auth, ssid, password);
}

void readAndUploadGasData() {
  // Read gas level from MQ-2 sensor
  gasLevel = analogRead(MQ2_PIN);  // Read analog value from MQ-2 sensor

  // Print gas level to serial monitor
  Serial.print("Gas Level: ");
  Serial.println(gasLevel);

  // Send gas level to Blynk on virtual pin V5
  Blynk.virtualWrite(V5, gasLevel);

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
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Continuously read and upload gas level data
  readAndUploadGasData();
  delay(1000);  // Check every 1 second (adjust delay as needed)
}
