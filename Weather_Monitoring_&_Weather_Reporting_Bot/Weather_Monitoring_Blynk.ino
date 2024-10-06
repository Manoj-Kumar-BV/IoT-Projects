#define BLYNK_TEMPLATE_ID "TMPL3eL5N9C-z"
#define BLYNK_TEMPLATE_NAME "Weather Monitoring"
#define BLYNK_AUTH_TOKEN "rL2fpT_U65dW46bE7IlHsGTJvELrNTJh"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Blynk credentials
char auth[] = BLYNK_AUTH_TOKEN; // Replace with your Blynk authentication token

// Wi-Fi credentials
char ssid[] = "OP";       // Replace with your Wi-Fi SSID
char pass[] = "12345678";  // Replace with your Wi-Fi password

// DHT sensor settings
#define DHTPIN 4         // Define the pin for DHT sensor data (e.g., GPIO4)
#define DHTTYPE DHT11    // DHT11 or DHT22
DHT dht(DHTPIN, DHTTYPE);

// Variables to hold temperature and humidity data
float temperature = 0;
float humidity = 0;

// Virtual pin for sending temperature and humidity to Blynk app
#define VPIN_TEMP V1   // Blynk virtual pin for temperature
#define VPIN_HUMID V2  // Blynk virtual pin for humidity

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize DHT sensor
  dht.begin();

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);
}

void readAndSendWeatherData() {
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

  // Send data to Blynk
  Blynk.virtualWrite(VPIN_TEMP, temperature);
  Blynk.virtualWrite(VPIN_HUMID, humidity);
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Read and send weather data every 10 seconds
  readAndSendWeatherData();
  delay(1000);  // Adjust delay as needed
}
