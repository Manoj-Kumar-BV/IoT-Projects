# Smart Lighting

## Overview
The Smart Lighting project utilizes an **ESP32** board along with an **LDR (Light Dependent Resistor)** sensor and an external LED. The system automatically controls the lighting based on ambient light conditions, providing an efficient way to manage lighting in different environments.

## Components Required
- **ESP32 board** (with built-in LED)
- **LDR sensor** (3 pins: VCC, GND, and OUT)
- **1 external LED**
- **Breadboard**
- **Jumper wires**

## Connections

### LDR Sensor
1. **VCC Pin**: Connect to the **3.3V** pin on the ESP32.
2. **GND Pin**: Connect to the **GND** pin on the ESP32.
3. **OUT Pin**: Connect the analog output to **GPIO 34** on the ESP32.

### External LED
1. **Anode (Longer leg)**: Connect to **GPIO 23** (LED_PIN2) on the ESP32.
2. **Cathode (Shorter leg)**: Connect to **GND** on the ESP32.

### Built-in LED
- The built-in LED on the ESP32 is already connected to **GPIO 2**. No additional wiring is needed for this.

## How It Works
The LDR sensor detects ambient light levels, and based on the readings, the system controls the external LED and the built-in LED. When the light level falls below a certain threshold, the LEDs turn on, providing illumination.

## Usage
This project can be used in various applications, such as smart home lighting systems, automated street lighting, and indoor lighting management based on natural light availability.
---
