# IoT Projects

This repository contains various IoT-based projects implemented using **ESP32** and different sensors. These projects aim to provide real-world smart solutions, from home automation to environmental monitoring.

## Table of Contents
- [Smart Lighting](#smart-lighting)
- [Smart Parking System](#smart-parking-system)
- [Intrusion Detection System](#intrusion-detection-system)
- [Weather Monitoring and Reporting Bot](#weather-monitoring-and-reporting-bot)
- [Smart Irrigation System](#smart-irrigation-system)
- [Forest Fire Detection System](#forest-fire-detection-system)
- [Installation](#installation)

## Projects Overview

### 1. Smart Lighting
A smart lighting system using **ESP32**, **LDR**, and the **Blynk app**. The system automatically controls the lighting based on ambient light conditions and allows manual override through the app.

#### Features:
- Automatic control using a light-dependent resistor (LDR).
- Manual control using the Blynk app.
- LED status tracking through Firebase or Blynk.

### 2. Smart Parking System
This system monitors the occupancy of parking slots using **IR sensors** and **ESP32**, sending real-time data to the Blynk app.

#### Features:
- Detection of parking slot occupancy using IR sensors.
- Real-time status updates in the Blynk app.
- Efficient space management for parking lots.

### 3. Intrusion Detection System
A security system that detects motion using a **PIR sensor** and an **ESP32**, and sends notifications when motion is detected.

#### Features:
- Motion detection using PIR sensors.
- Real-time alerts via Firebase or Blynk.
- Easy-to-implement home security solution.

### 4. Weather Monitoring and Reporting Bot
A weather station built using an **ESP32** and a **DHT11 sensor** for monitoring temperature and humidity, along with real-time data reporting.

#### Features:
- Monitors temperature and humidity.
- Displays weather data on Blynk/Firebase.
- Potential to add more sensors for comprehensive environmental monitoring.

### 5. Smart Irrigation System
This project automates irrigation based on soil moisture levels, ensuring optimal water usage. It uses a **soil moisture sensor**, **DHT11**, and **ESP32**.

#### Features:
- Automatic irrigation control.
- Monitoring of soil moisture, temperature, and humidity.
- Remote control and monitoring through Blynk.

### 6. Forest Fire Detection System
A system for detecting forest fires in real time using a **temperature sensor**, **humidity sensor**, and **ESP32**. Alerts are sent to notify users of potential fire hazards.

#### Features:
- Detection of abnormal temperature and humidity changes.
- Early fire hazard warnings.
- Real-time alerts via Blynk.

## Installation

### Prerequisites
- **Arduino IDE** for programming ESP32.
- ESP32 development board.
- Sensors: LDR, PIR, IR, Soil Moisture Sensor, DHT11, etc.
- Install libraries: `Blynk`, `FirebaseESP32`, `DHT`, `WiFi`, etc.

### Setup
1. Clone the repository:
   ```bash
   git clone https://github.com/Manoj-Kumar-BV/IoT-Projects
   ```
2. Open the specific project folder in Arduino IDE.
3. Connect the ESP32 to your system and upload the project.

## Contributing
Feel free to submit issues and pull requests if you find bugs or want to add new features. Contributions are welcome!
---
