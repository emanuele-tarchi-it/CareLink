# 🗺️ CareLink Mesh System — Roadmap v0.2
> **From bedside monitoring to a human‑centered clinical support ecosystem.**

---

## ✅ v0.1 — Foundations (Completed)
**Goal:** Establish the hardware baseline and core communication layer.

- [x] HW‑364A validation (ESP8266 + integrated OLED)
- [x] Identification of non‑standard I2C mapping (SDA:14, SCL:12)
- [x] Basic ESP‑NOW handshake between Patient and Nurse nodes

---

## 🔄 v0.2 — Clinical Intelligence & Identity (In Progress)
**Goal:** Give CareLink a clinical purpose and a clear project identity.

- [x] Sensor Integration: MAX30102 (SpO₂/BPM) + MAX30205 (Temp)
- [x] Edge Clinical Logic: Simplified Shock Index (sSI), Infection Alert
- [x] Visual Urgency: OLED strobe via `invertDisplay()`
- [x] Project Identity: README rewritten with mission, vision, and clinical context
- [ ] Robust ACK: Refinement of the 1‑byte binary acknowledgment protocol

---

## 📅 v0.3 — Configuration, Identity & Clinical Roles
**Goal:** Introduce identity, pairing, and the first layer of clinical hierarchy.  
*(Nurse remains the primary decision-maker.)*

- [ ] Captive Portal: Configure `bed_id` and Nurse MAC without reflashing
- [ ] EEPROM Storage: Persistent configuration across power cycles
- [ ] Dynamic Pairing: “Tap‑to‑pair” logic between Nurse and Patient nodes
- [ ] Clinical Escalation Model:
  - Patient Node → Nurse Node (always first)
  - Nurse Node validates, contextualizes, and decides whether to escalate
  - No direct alerts to physicians

---

## 📡 v0.4 — Gateway & Local Dashboard
**Goal:** Introduce persistence, supervision, and ward‑level visibility.

- [ ] Gateway Node: ESP32 hub bridging ESP‑NOW → Wi‑Fi/MQTT
- [ ] Self‑Healing Mesh: Multi‑hop forwarding for extended coverage
- [ ] Local Dashboard: Real‑time ward overview (web UI hosted on Gateway)

---

## 🩺 v0.5 — Doctor Node (Supervisory Station)
**Goal:** Add a fixed clinical workstation for validated escalation only.  
*(Never bypassing the nurse.)*

- [ ] Doctor Node: Trend visualization, validated alerts, operational messages
- [ ] Nurse → Doctor Messaging: “Therapy updated”, “Check Bed 5”, etc.
- [ ] Specialist Requests (Scalable):
  - Optional contact with anesthesiology, resuscitation, respiratory therapy
  - Modular design for future departmental integration

---

## ⚡ v0.6 — LoRa Emergency Layer
**Goal:** Ensure survival during total infrastructure failure.

- [ ] LoRa Integration: Tertiary fallback for SOS/Help messages
- [ ] Battery Optimization: Deep‑sleep for mobile Nurse Nodes

---

## ☁️ v1.0 — Cloud & Analytics
**Goal:** Enterprise‑grade monitoring, auditing, and predictive insights.

- [ ] AWS/Azure Bridge: Secure telemetry upload
- [ ] Advanced Analytics: Trend‑based deterioration prediction
- [ ] Security Hardening: AES‑128 encryption for all peer‑to‑peer packets

---

## ⚠️ Disclaimer
CareLink Mesh System is a technical and educational prototype inspired by real clinical workflows.  
It is **not** a certified medical device and must not be used for life‑critical monitoring.
