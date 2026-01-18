# 🗺️ CareLink Mesh System — Roadmap v0.2
> **Evolution from local prototype to a clinical-grade resilient IoT network.**

---

## ✅ v0.1 — Foundations (Completed)
**Goal:** Establish core communication and hardware baseline.
- [x] Hardware validation for **HW-364A** (ESP8266 + OLED).
- [x] Identification of non-standard I2C pinout (SDA:14, SCL:12).
- [x] Basic ESP-NOW peer-to-peer handshake between Patient and Nurse nodes.

---

## 🔄 v0.2 — Clinical Intelligence (In Progress)
**Goal:** Transform raw data into actionable medical alerts.
- [x] **Sensor Integration**: MAX30102 (SpO2/BPM) and MAX30205 (Body Temp) on a shared I2C bus.
- [x] **Edge Computing**: Implementation of **Simplified Shock Index (sSI)** and **Infection Alert** logic.
- [x] **Visual Feedback**: Emergency strobe effect via OLED `invertDisplay()`.
- [ ] **Robust ACK**: Refinement of the 1-byte binary acknowledgment protocol.

---

## 📅 v0.3 — Configuration & Identity
**Goal:** Ease of deployment and ward management.
- [ ] **Captive Portal**: Web interface to configure `bed_id` and Nurse MAC address without re-flashing.
- [ ] **EEPROM Storage**: Save configuration locally to survive power cycles.
- [ ] **Dynamic Pairing**: "Tap-to-pair" logic between Nurse and Patient nodes.

---

## 📡 v0.4 — Mesh & Gateway Integration
**Goal:** Expanding the network range and data persistence.
- [ ] **Gateway Node**: ESP32-based hub to bridge ESP-NOW data to Wi-Fi/MQTT.
- [ ] **Self-Healing Mesh**: Basic multi-hop forwarding if a node is out of direct range.
- [ ] **Local Dashboard**: Simple web UI hosted on the Gateway for real-time ward overview.

---

## ⚡ v0.5 — LoRa Emergency Layer
**Goal:** Survival in total infrastructure blackout.
- [ ] **LoRa Integration**: Tertiary fallback for critical "SOS" and "Help" messages only.
- [ ] **Battery Optimization**: Deep-sleep cycles for battery-powered Nurse Nodes.

---

## ☁️ v1.0 — Cloud & Analytics
**Goal:** Enterprise-grade monitoring and historical data.
- [ ] **AWS/Azure Bridge**: Secure telemetry upload for medical auditing.
- [ ] **Advanced Analytics**: Trend analysis for patient deterioration prediction.
- [ ] **Security Hardening**: AES-128 encryption for all peer-to-peer packets.

---

## ⚠️ Disclaimer
CareLink Mesh System is a technical and educational prototype. It is not a certified medical device and is not intended for life-critical monitoring.
