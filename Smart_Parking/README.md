---

# Smart Parking System

## Overview
The Smart Parking System project utilizes an **ESP32** board and **IR Sensors** to monitor parking slot occupancy. This system aims to provide real-time data on available parking spaces, enhancing the efficiency of parking management in urban areas.

## Components Required
- **ESP32 board** (with built-in LED)
- **2 IR Sensors**
- **Jumper wires**

## Connections

### IR Sensors to ESP32
1. **IR Sensor 1:**
   - **VCC Pin**: Connect the VCC pin of IR Sensor 1 to the **3.3V** pin on the ESP32.
   - **GND Pin**: Connect the GND pin of IR Sensor 1 to the **GND** pin on the ESP32.
   - **OUT Pin**: Connect the OUT pin (analog output) of IR Sensor 1 to **GPIO 34** on the ESP32.

2. **IR Sensor 2:**
   - **VCC Pin**: Connect the VCC pin of IR Sensor 2 to the **3.3V** pin on the ESP32.
   - **GND Pin**: Connect the GND pin of IR Sensor 2 to the **GND** pin on the ESP32.
   - **OUT Pin**: Connect the OUT pin (analog output) of IR Sensor 2 to **GPIO 35** on the ESP32.

## How It Works
The Smart Parking System continuously monitors the occupancy of two parking slots using the connected IR sensors. When a vehicle is detected by an IR sensor, it can trigger an alert or update a display to inform users of the parking status. This system enhances parking efficiency and helps drivers locate available spaces quickly.

## Usage
This project can be deployed in various parking facilities, including public parking lots, shopping centers, and urban areas, to improve user experience and optimize space utilization.

---
