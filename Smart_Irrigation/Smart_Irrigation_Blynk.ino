#define BLYNK_TEMPLATE_ID "TMPL3kuPxGJ03"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation"
#define BLYNK_AUTH_TOKEN "OLku2XPo84fdsJamy84U1seHns5n1Lx3"


#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

// Blynk Auth Token from the Blynk app
char auth[] = BLYNK_AUTH_TOKEN; // Replace with your Blynk Auth Token

// Wi-Fi credentials
const char* ssid = "OP";       // Replace with your Wi-Fi SSID
const char* password = "12345678";   // Replace with your Wi-Fi password

// Sensor pins
#define MOISTURE_PIN 34  // Pin for soil moisture sensor (analog input GPIO34)
#define DHT_PIN 27       // Pin for DHT11 sensor (GPIO27)
#define DHT_TYPE DHT11   // Define DHT sensor type (DHT11)
DHT dht(DHT_PIN, DHT_TYPE);

// Virtual Pins for Blynk
#define VIRTUAL_MOISTURE V1  // Virtual pin for soil moisture
#define VIRTUAL_TEMP V2      // Virtual pin for temperature
#define VIRTUAL_HUMIDITY V3  // Virtual pin for humidity

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize sensor pins and DHT sensor
  pinMode(MOISTURE_PIN, INPUT);
  dht.begin();

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

void readAndUploadSensorData() {
  // Read soil moisture level (analog value)
  int moistureLevel = analogRead(MOISTURE_PIN);

  // Read temperature and humidity from DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Print the sensor data to the serial monitor
  Serial.print("Moisture level: ");
  Serial.println(moistureLevel);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Humidity: ");
  Serial.println(humidity);

  // Send sensor data to Blynk (Virtual pins)
  Blynk.virtualWrite(VIRTUAL_MOISTURE, moistureLevel);
  Blynk.virtualWrite(VIRTUAL_TEMP, temperature);
  Blynk.virtualWrite(VIRTUAL_HUMIDITY, humidity);
}

void loop() {
  // Run Blynk in the background
  Blynk.run();

  // Continuously read and upload sensor data
  readAndUploadSensorData();
  delay(10000);  // Adjust delay as needed
}
