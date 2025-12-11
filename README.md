# IOT Projects

## Index

1. [Traffic Density Controller](#1---traffic-density-controller)

## 1 - Traffic Density Controller
**Traffic Density Controller** is a beginner-friendly Arduino project that demonstrates real-time distance sensing using an HC-SR04 ultrasonic sensor and visual traffic-status feedback using red, yellow, and green LEDs. It’s great for learning basic electronics, sensor interfacing, and Arduino programming — and it works both on a physical breadboard and in Tinkercad simulation.

---

### Table of Contents

* [Overview](#overview)
* [Features](#features)
* [Hardware Components](#hardware-components)
* [Circuit Connections](#circuit-connections)
* [How It Works](#how-it-works)
* [Simulation (Tinkercad)](#simulation-tinkercad)

---

### Overview

This project simulates a simple smart traffic signal that updates LED indicators based on the proximity of a detected object (vehicle). The ultrasonic sensor measures distance and the Arduino switches LEDs to represent traffic density:
![Traffic Sensor Setup](Images/Traffic.png)
* **Green** — Road clear (object far)
* **Yellow** — Moderate traffic (object approaching)
* **Red** — Heavy traffic / object very close

### Features

* Distance measurement with Sensor
* Real-time traffic status using 3 LEDs (R/Y/G)
* Works on physical hardware and Tinkercad
* Simple, modular wiring and code (beginner-friendly)

## Hardware Components

* Arduino Uno (or compatible)
* HC-SR04 ultrasonic distance sensor
* 1 × Red LED
* 1 × Yellow LED
* 1 × Green LED
* 3 × 220 Ω resistors
* Breadboard
* Jumper wires

> Optional: USB cable for programming, small enclosure or mounting hardware for deployment

## Circuit Connections

**Ultrasonic Sensor (HC-SR04)**

* `TRIG` → Arduino **Pin 9**
* `ECHO` → Arduino **Pin 10**
* `VCC` → Arduino **5V**
* `GND` → Arduino **GND**

**LED Indicators**

* Red LED (long leg / anode) → Arduino **Pin 2** → 220 Ω resistor → GND rail
* Yellow LED → Arduino **Pin 3** → 220 Ω resistor → GND rail
* Green LED → Arduino **Pin 4** → 220 Ω resistor → GND rail

**Ground**

* Breadboard GND rail → Arduino **GND**

*(Include a circuit diagram or Tinkercad screenshot in the `docs/` folder or repository root.)*

## How It Works

1. The HC-SR04 sends a short ultrasonic pulse from `TRIG` and listens for the echo on `ECHO`.
2. Arduino measures the time between sent pulse and received echo and converts it to distance (usually in centimeters).
3. Based on pre-defined distance thresholds, the Arduino sets the LED states:

   * `distance > X cm` → **Green ON** (clear)
   * `Y cm < distance <= X cm` → **Yellow ON** (moderate)
   * `distance <= Y cm` → **Red ON** (heavy/close)
4. These thresholds can be adjusted in the code to better match your demo setup.

## Simulation (Tinkercad)

1. Create a new Arduino circuit in Tinkercad and add an HC-SR04, three LEDs, resistors, and the Arduino Uno.
2. Wire according to the Circuit Connections section.
3. Copy the Arduino sketch into Tinkercad’s code editor and start the simulation.
4. Move the simulated object (or change the sensor input) to observe LED transitions.
