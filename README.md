# 🏥 CareLink Mesh System
## *Version 0.2 - Clinical Intelligence & Edge Monitoring*

![Version](https://img.shields.io/badge/Version-0.2--EN-blue)
![Platform](https://img.shields.io/badge/Platform-ESP8266--HW364A-orange)
![Framework](https://img.shields.io/badge/Framework-Arduino/PlatformIO-blue)
![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)

CareLink Mesh System is a resilient IoT network for hospital wards, enabling reliable bedside monitoring, nurse alerts, and emergency requests. It operates across Wi-Fi and ESP-NOW to ensure continuous communication even during network outages.

---

## 🚀 Key Features (v0.2)

- **Real-Time Vitals Monitoring**: Integrated support for SpO2, Heart Rate, and Body Temperature.
- **Clinical Decision Support**: Edge-computing algorithms for **Simplified Shock Index (sSI)** and **Infection Alert**.
- **Resilient Connectivity**: Primary Wi-Fi link with automatic **ESP-NOW binary fallback**.
- **Visual Urgency System**: High-contrast OLED strobe effects for critical unacknowledged alarms.

---

## 🔧 Hardware Configuration (Patient Node)

The system is optimized for the **HW-364A (ESP8266 with integrated OLED)**.

### Custom I2C Pinout
Due to non-standard manufacturer mapping, the sensors must be initialized as follows:
- **SDA**: GPIO 14 (D5)
- **SCL**: GPIO 12 (D6)

### Sensor Matrix
| Sensor | Model | Function | I2C Address |
| :--- | :--- | :--- | :--- |
| **OLED** | SSD1306 | Local UI & Visual Alarms | `0x3C` |
| **Pulse Ox** | MAX30102 | Heart Rate & SpO2 | `0x57` |
| **Temp** | MAX30205 | Clinical Body Temperature | `0x48` |



---

## 🧠 Clinical Logic

Firmware v0.2 processes data locally to reduce alarm fatigue and prioritize critical cases:

1. **Simplified Shock Index (sSI)**: 
   - Formula: `Heart Rate / SpO2`. 
   - Alert triggers if `sSI > 1.0` (indicates potential hemodynamic instability).
2. **Infection Alert**: 
   - Triggers if `Temp > 38.0°C` in conjunction with `BPM > 100` or desaturation.

---

## 📡 Communication Protocol

- **Wi-Fi**: Primary channel for gateway logging and cloud sync.
- **ESP-NOW**: Binary-optimized, low-latency peer-to-peer fallback.
- **Retries**: 3-stage ACK logic with a 500ms timeout per retry.

---

## 🗺️ Roadmap

- [x] **v0.1 - Local Prototype**: Basic Wi-Fi communication and ACK flow.
- [x] **v0.2 - Clinical Intelligence**: Hardware-specific I2C mapping, sSI calculation, and binary protocol.
- [ ] **v0.3 - Identity Management**: Captive portal for bedside configuration (Bed ID / Nurse MAC) and EEPROM storage.
- [ ] **v1.0 - Cloud Integration**: AWS Lambda & DynamoDB for historical auditing and ward-wide dashboards.

---

## ⚠️ Disclaimer

This project is a technical and educational prototype inspired by clinical workflows. **It is not a certified medical device** and is not intended for life-critical monitoring or diagnostic use.
