---

# Weather Monitoring System

## Overview
The Weather Monitoring System project utilizes an **ESP32** board and a **DHT11 sensor** to measure temperature and humidity. This system provides real-time weather data, making it suitable for applications such as smart homes, agricultural monitoring, and environmental monitoring.

## Components Required
- **ESP32 board**
- **DHT11 sensor** (3 pins: VCC, GND, and DATA)
- **Jumper wires**

## Connections

### DHT11 Sensor to ESP32
1. **VCC Pin**: Connect the VCC pin of the DHT11 sensor to the **3.3V** pin on the ESP32.
2. **GND Pin**: Connect the GND pin of the DHT11 sensor to the **GND** pin on the ESP32.
3. **DATA Pin**: Connect the DATA pin of the DHT11 sensor to **GPIO 15** on the ESP32 (or any other GPIO pin of your choice).

### ESP32 Power Supply
- Ensure that your ESP32 is powered via **USB** or **external power**, as per your project setup.

## How It Works
The Weather Monitoring System continuously reads data from the DHT11 sensor, providing temperature and humidity measurements. This data can be used for various applications, such as controlling HVAC systems, monitoring plant health, and providing weather information.

## Usage
This project can be implemented in various settings, including:
- Home automation systems
- Agricultural monitoring to ensure optimal growing conditions
- Environmental data logging for research purposes

---
