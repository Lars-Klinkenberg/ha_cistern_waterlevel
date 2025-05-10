# Cistern Water Level Sensor with ESP32 + Home Assistant

This project monitors the water level in a rainwater cistern using two ESP32s, some ultrasonic wizardry, and Home Assistant. One ESP32 lives in the cistern (moist and miserable), the other chills in the house and communicates via serial over a good ol’ CAT cable. The indoor unit connects to Home Assistant through ESPHome.

## 💡 How it works

- **ESP32 (Tank Unit):**  
  Measures distance to water surface using an ultrasonic sensor (JSN-SR04T).  
  Sends raw distance data via UART.

- **ESP32 (House Unit):**  
  Reads serial data from the tank unit over CAT cable.  
  Integrated into Home Assistant using ESPHome.  
  Publishes the water level as a sensor.

## ❓ Why Two ESP32s?

The cistern is to far from the house (and WiFi). Instead of fighting with flaky wireless through meters of dirt, stone, and disappointment, we split the job:

    The Tank ESP32 handles just the sensor and sends raw data via UART.

    The House ESP32 sits indoors with proper WiFi and talks to Home Assistant via ESPHome.

They're connected using a standard CAT5/6 cable, which carries serial data reliably over distance — no need to mess with WiFi repeaters, underground cabling, or black magic. Just good old serial comms, like it's 1999.


## 🧰 Stuff you'll need

- 2× ESP32 boards  
- 1× Ultrasonic distance sensor (waterproof if you're smart)  
- CAT5/6 cable for serial comms  
- Power supply
