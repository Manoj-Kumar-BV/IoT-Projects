#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>

// Firebase configuration
#define FIREBASE_HOST "https://weather-monitoring-53402-default-rtdb.firebaseio.com/" // Replace with your Firebase host URL
#define FIREBASE_AUTH "68SEb1GTMziHslTZmYIvBaRbS9lNllfiOd4o3H47"                   // Replace with your Firebase authentication token

// Define Firebase and Wi-Fi credentials
FirebaseData firebaseData;
FirebaseConfig firebaseConfig;
FirebaseAuth firebaseAuth;

// Wi-Fi credentials
const char* ssid = "OP";      // Replace with your Wi-Fi SSID
const char* password = "12345678";  // Replace with your Wi-Fi password

// DHT sensor settings
#define DHTPIN 4         // Define the pin for DHT sensor data (e.g., GPIO4)
#define DHTTYPE DHT11    // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

// Variables to hold temperature and humidity data
float temperature = 0;
float humidity = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize DHT sensor
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

void readAndUploadWeatherData() {
  // Read temperature and humidity from DHT sensor
  temperature = dht.readTemperature();  // Temperature in Celsius
  humidity = dht.readHumidity();        // Humidity in percentage

  // Check if readings are valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print weather data to serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C");
  Serial.print("  Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  // Send data to Firebase
  Firebase.setFloat(firebaseData, "/weather/temperature", temperature);
  Firebase.setFloat(firebaseData, "/weather/humidity", humidity);
}

void loop() {
  // Continuously read and upload weather data
  readAndUploadWeatherData();
  delay(10000);  // Check every 10 seconds (adjust delay as needed)
}
