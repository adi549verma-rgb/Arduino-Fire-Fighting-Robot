#  Arduino Fire Fighting Robot

An autonomous fire-fighting robot developed using **Arduino Uno** that detects fire using multiple flame sensors, avoids obstacles, and extinguishes flames automatically using a servo-controlled water nozzle and DC water pump.

---

## Project Overview

This project was developed as a **Minor Project** for the **B.Tech in Electronics & Communication Engineering** at **Jawaharlal Nehru Government Engineering College (JNGEC), Sundernagar, Himachal Pradesh**.

The robot continuously patrols its surroundings, detects fire from different directions, navigates toward the flame, and extinguishes it without human intervention.

---

## Features

-  Automatic fire detection using three flame sensors
-  Autonomous navigation
-  Obstacle detection using HC-SR04 ultrasonic sensor
-  Automatic water spraying system
-  Servo-controlled nozzle movement
-  Differential drive motor control
-  Rechargeable battery-powered operation

---

## Hardware Components

- Arduino Uno R3
- 3 × IR Flame Sensors
- HC-SR04 Ultrasonic Sensor
- L293D Motor Driver
- 2 × DC Geared Motors
- Servo Motor (SG90/MG90S)
- DC Water Pump
- Water Tank
- Robot Chassis
- Rechargeable Battery Pack

---

## Software

- Arduino IDE
- Embedded C / Arduino Programming

---

## Working Principle

1. The robot moves forward while continuously scanning for obstacles.
2. The HC-SR04 sensor detects nearby obstacles and changes the robot's path if necessary.
3. Three flame sensors monitor the left, center, and right sides for fire.
4. When a flame is detected, the robot rotates toward the fire source.
5. The robot approaches the flame until it reaches a safe extinguishing distance.
6. The servo motor sweeps the water nozzle while the DC pump sprays water.
7. After extinguishing the fire, the robot resumes patrolling.

---

## Repository Structure

```
Arduino-Fire-Fighting-Robot/
│
├── README.md
├── fire_fighting_robot.ino
├── Circuit_Diagram.png
├── Block_Diagram.png

├── images/
│   ├── blocck diagram.jpg
│   ├── Circuit_Diagram.png

```

---

## Pin Configuration

| Component | Arduino Pin |
|------------|------------:|
| Flame Sensor (Left) | D8 |
| Flame Sensor (Center) | D9 |
| Flame Sensor (Right) | D10 |
| Motor ENA | D5 (PWM) |
| Motor IN1 | D6 |
| Motor IN2 | D7 |
| Motor ENB | D11 (PWM) |
| Motor IN3 | D12 |
| Motor IN4 | D13 |
| Servo Motor | D3 |
| Water Pump | D4 |
| Ultrasonic TRIG | A0 |
| Ultrasonic ECHO | A1 |

---

---

## Future Improvements

- ESP32 + Wi-Fi monitoring
- IoT-based fire alerts
- Thermal camera integration
- Smoke and gas sensors
- AI-based flame detection
- Mobile app control

---

## Documentation

- Arduino Source Code (`fire_fighting_robot.ino`)
- Circuit Diagram
- Block Diagram
- Flowchart


---

## Author

**Aditya Verma**

B.Tech Electronics & Communication Engineering

Jawaharlal Nehru Government Engineering College (JNGEC), Sundernagar, Himachal Pradesh

---

 If you found this project useful, consider giving it a Star.
