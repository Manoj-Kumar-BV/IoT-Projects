#include <WiFi.h>
#include <FirebaseESP32.h>
#include "DHT.h"

// Firebase configuration
#define FIREBASE_HOST "https://smart-irrigation-ee740-default-rtdb.firebaseio.com/" // Replace with your Firebase host URL
#define FIREBASE_AUTH "SYaCB4QRxCy0NZFObIrKzmBaX5mEslJUUUEBOfjq"  // Replace with your Firebase authentication token

// Wi-Fi credentials
const char* ssid = "OP";      // Replace with your Wi-Fi SSID
const char* password = "12345678";  // Replace with your Wi-Fi password

// Firebase objects
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Sensor pins
#define MOISTURE_PIN 34  // Pin for soil moisture sensor (analog input GPIO34)
#define DHT_PIN 27       // Pin for DHT11 sensor (GPIO27)
#define DHT_TYPE DHT11   // Define DHT sensor type (DHT11)
DHT dht(DHT_PIN, DHT_TYPE);

// Threshold for soil moisture (you can still keep it for display purposes)
int moistureThreshold = 500;

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

  // Firebase configuration
  firebaseConfig.host = FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&firebaseConfig, &firebaseAuth);
  Firebase.reconnectWiFi(true);
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

  // Send sensor data to Firebase
  Firebase.setInt(firebaseData, "/smart_irrigation/moisture_level", moistureLevel);
  Firebase.setFloat(firebaseData, "/smart_irrigation/temperature", temperature);
  Firebase.setFloat(firebaseData, "/smart_irrigation/humidity", humidity);
}

void loop() {
  // Continuously read and upload sensor data
  readAndUploadSensorData();
  delay(10000);  // Adjust delay as needed
}
