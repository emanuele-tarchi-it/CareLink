---

# CareLink Mesh System
## *Version 0.1 - Local Prototype*

![Version](https://img.shields.io/badge/Version-0.1--EN-green)
![Python](https://img.shields.io/badge/Python-3.8%2B-blue)
![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)

CareLink Mesh System is a resilient IoT network designed for hospital wards, built to ensure reliable communication between bedside patient nodes and nursing staff—even in scenarios where the primary network is unavailable.

🎯 Purpose

Provide a nursing support and alert system that:

• monitors patients through dedicated bedside nodes
• notifies alarms to portable nurse devices
• allows alarm acknowledgment with operator ID, timestamp, and event type
• enables nurses to request assistance from colleagues
• remains fully operational even during Wi‑Fi outages


🧩 Architecture (v0.1 – local prototype)

• Patient Node (ESP8266/ESP32)
Installed at the patient’s bedside, powered from mains with backup battery. Can integrate sensors (e.g., vitals, motion) and sends alerts to the system.
• Nurse Node (ESP32/M5Stack)
Portable devices with rechargeable battery, display, and physical buttons:• alarm acknowledgment (with visual confirmation)
• assistance request (with anti‑accidental activation logic)

• Gateway
A central node (ESP32 or PC running a Python script) that:• receives alerts
• logs events
• synchronizes information across nodes



📡 Communication Channels

• Wi‑Fi – primary channel for communication with the gateway and PC
• ESP‑NOW – low‑latency fallback for direct node‑to‑node communication
• (Future) LoRa Mesh – long‑range emergency network ensuring continuity during extended outages


🗺️ Roadmap

• v0.1 – Local Prototype• Patient Node → Gateway (Wi‑Fi)
• Nurse Node → Gateway (Wi‑Fi)
• Basic alarm acknowledgment with simple logging (file or console)

• v0.2 – ESP‑NOW Fallback• Direct communication between nodes when Wi‑Fi is unavailable
• Basic ACK and retransmission logic

• v0.3 – LoRa Mesh (experimental)• Multi‑hop routing
• Low‑bandwidth critical messaging

• v1.0 – Cloud Integration (AWS‑ready)• API Gateway + Lambda
• DynamoDB for event logs
• Basic dashboard



⚠️ Disclaimer

This project is inspired by real‑world clinical experience and is intended as a technical and educational prototype.
It is not a certified medical device.

---