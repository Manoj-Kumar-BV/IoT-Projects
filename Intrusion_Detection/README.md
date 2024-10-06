---

# Intrusion Detection System

## Overview
The Intrusion Detection System project utilizes an **ESP32** board along with a **PIR Motion Sensor** and an LED. This system detects motion and alerts users by illuminating an LED, providing a simple yet effective way to monitor areas for unauthorized access.

## Components Required
- **ESP32 board**
- **PIR Motion Sensor**
- **1 LED**
- **Jumper wires**

## Connections

### PIR Sensor
1. **VCC Pin**: Connect the VCC pin of the PIR sensor to the **3.3V** pin on the ESP32.
2. **GND Pin**: Connect the GND pin of the PIR sensor to the **GND** pin on the ESP32.
3. **OUT Pin**: Connect the OUT pin of the PIR sensor to **GPIO 34** on the ESP32.

### LED
1. **Anode (Long leg)**: Connect the anode of the LED to **GPIO 5** on the ESP32.
2. **Cathode (Short leg)**: Connect the cathode of the LED to **GND** with a suitable resistor (e.g., **220Ω**).

### Built-in LED
- The built-in LED on the ESP32 is already connected to **GPIO 2**. No additional wiring is needed for this.

## How It Works
The PIR Motion Sensor detects motion in its field of view. When motion is detected, the OUT pin goes HIGH, triggering the LED to illuminate as a visual alert. This setup is ideal for security applications in homes, offices, or restricted areas.

## Usage
This project can be implemented in various scenarios, including home security systems, motion-triggered alerts, and automated monitoring of specific areas.

---
