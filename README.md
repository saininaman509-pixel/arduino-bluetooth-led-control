# Smart Bluetooth LED Control System

## Overview

This project is a Bluetooth-controlled LED automation system built using Arduino Uno.  
It allows wireless control of six LEDs through a mobile phone while displaying live status updates on an LCD screen.

The system demonstrates embedded programming, serial communication, hardware interfacing, and real-time control using Arduino.

---

## Features

- Wireless LED control using Bluetooth
- Controls 6 individual LEDs
- Simultaneous blinking mode
- Brightness control using PWM
- Emergency signal flashing mode
- Real-time LCD status display
- Custom text display on LCD
- Expandable for home automation projects

---

## Components Used

- Arduino Uno
- HC-05 Bluetooth Module
- 16x2 LCD Display
- Breadboard
- 6 LEDs
- Resistors
- Jumper Wires
- USB Power Supply

---

## Design & Development

### Arduino Control Unit
Arduino Uno acts as the main controller, receiving commands from the Bluetooth module and controlling outputs accordingly.

### Bluetooth Communication
The HC-05 module receives commands from a mobile phone and sends them to Arduino through serial communication.

### LED Output Section
Six LEDs are connected as independent outputs to demonstrate lighting control and signal patterns.

### LCD Interface
The LCD provides live feedback such as LED status, active mode, and custom text messages.

---

## Working Principle

1. User sends command from mobile phone  
2. Bluetooth module receives command  
3. Arduino processes input  
4. LEDs perform selected action  
5. LCD updates system status instantly

---

## Applications

- Smart home lighting prototype
- Wireless appliance control
- Embedded systems learning
- Arduino beginner project
- IoT foundation project

---

## Future Improvements

- Relay control for real appliances
- Mobile app interface
- Voice assistant control
- Wi-Fi control using ESP32
- Sensor-based automation

---

## Author

Naman Saini
