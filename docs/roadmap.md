# CareLink Roadmap

## v0.2 — Clinical Intelligence (COMPLETED)
- MAX30102 integration
- MAX30205 integration
- SpO₂, HR, Temperature
- Shock Index calculation
- Infection Alert logic
- Clinical OLED display
- Serial telemetry output

---

## v0.3 — Configuration & Pairing (CURRENT)
- Captive Portal for initial setup
- EEPROM persistent configuration
- Bed ID assignment
- Nurse MAC assignment
- Secure pairing handshake (ESP-NOW)
- OLED pairing feedback
- Gateway pairing event logging
- Documentation updates

---

## v0.4 — Clinical Telemetry (NEXT)
- Re-enable MAX30102 + MAX30205
- Integrate clinical logic with pairing
- Send vitals to Nurse Node
- Nurse Node displays alerts
- Gateway logs vitals + alerts
- MQTT publishing (optional)
- config.yaml used by gateway

---

## v0.5 — Escalation & Doctor Node
- Doctor Node role
- Escalation logic (Nurse → Doctor)
- Multi-node alert routing
- Prioritization of critical events
- Gateway dashboard (basic)

---

## v0.6 — Mesh Networking
- LoRa mesh backbone
- Multi-hop routing
- Redundant paths
- Ward-wide coverage
- Offline-first behavior

---

## v1.0 — Production Candidate
- OTA updates
- Enclosure + hardware revision
- Battery optimization
- Clinical trial preparation
