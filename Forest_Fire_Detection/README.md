---

# Forest Fire Detection

## Overview
The Forest Fire Detection project utilizes an **ESP32** board along with an **MQ-2 Gas Sensor** and an external LED. This system aims to detect gas levels indicative of a fire and alerts users by illuminating an LED.

## Components Required
- **ESP32 board** (with built-in LED)
- **MQ-2 Gas Sensor** (4 pins: VCC, GND, AO, DO)
- **1 external LED**
- **Breadboard**
- **Jumper wires**

## Connections

### MQ-2 Gas Sensor
1. **VCC (Power pin)**: Connect the VCC pin of the MQ-2 sensor to the **3.3V** pin on the ESP32.
2. **GND (Ground pin)**: Connect the GND pin of the MQ-2 sensor to the **GND** pin on the ESP32.
3. **AO (Analog Output)**: Connect the AO pin of the MQ-2 sensor to **GPIO 34** (analog input pin) on the ESP32.
4. **DO (Digital Output)**: (Optional) If you want to use the digital output feature, you can connect the DO pin to any available GPIO pin.

### External LED
1. **Anode (Longer leg)**: Connect the anode of the external LED to **GPIO 5** on the ESP32.
2. **Cathode (Shorter leg)**: Connect the cathode of the external LED to **GND** on the ESP32.

### Built-in LED
- The built-in LED on the ESP32 is already connected to **GPIO 2**. No additional wiring is needed for this.

## How It Works
The MQ-2 Gas Sensor detects gas levels, which can indicate the presence of fire. When gas concentrations exceed a predefined threshold, the external LED lights up, providing a visual alert for potential fire hazards.

## Usage
This project can be applied in various scenarios, including forest fire monitoring, home safety systems, and any situation where gas detection is critical for early warning.

---
