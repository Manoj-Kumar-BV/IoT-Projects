---

# Smart Irrigation System

## Overview
The Smart Irrigation System project utilizes an **ESP32** board, a **DHT11 Sensor**, and a **Soil Moisture Sensor** to monitor and manage soil moisture levels and environmental conditions. This system aims to optimize irrigation processes, ensuring that plants receive adequate water based on real-time moisture data.

## Components Required
- **ESP32**
- **DHT11 Sensor**
- **Soil Moisture Sensor**

## Connections

### Soil Moisture Sensor to ESP32
1. **VCC (Power) Pin**: Connect the VCC pin of the soil moisture sensor to the **3.3V** pin on the ESP32.
2. **GND (Ground) Pin**: Connect the GND pin of the soil moisture sensor to the **GND** pin on the ESP32.
3. **Analog Output Pin (A0)**: Connect the analog output pin of the soil moisture sensor to **GPIO 34** on the ESP32 (this is defined as **MOISTURE_PIN** in the code).

### DHT11 Sensor to ESP32
1. **VCC (Power) Pin**: Connect the VCC pin of the DHT11 sensor to the **3.3V** pin on the ESP32.
2. **GND (Ground) Pin**: Connect the GND pin of the DHT11 sensor to the **GND** pin on the ESP32.
3. **Data (Signal) Pin**: Connect the data pin of the DHT11 sensor to **GPIO 27** on the ESP32 (this is defined as **DHT_PIN** in the code).

## How It Works
The Smart Irrigation System continuously monitors soil moisture levels and environmental parameters (temperature and humidity) using the connected sensors. Based on the moisture readings, the system can be programmed to trigger irrigation actions, ensuring optimal watering for plants and conserving water resources.

## Usage
This project can be implemented in various agricultural and gardening applications, allowing for automated irrigation based on real-time data, reducing manual intervention, and improving plant health.


---
