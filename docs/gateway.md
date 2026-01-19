# CareLink — Nurse Gateway

The Nurse Gateway is the central coordinator of the CareLink ecosystem.  
It aggregates bedside data, manages alerts, and ensures system resilience.

---

## 🟦 Responsibilities

- Receive and validate data from bedside nodes  
- Manage alert workflows  
- Handle emergency requests  
- Maintain acknowledgment loops  
- Provide fallback communication during network instability  
- Prepare data for future cloud dashboards  

---

## 🔄 Communication Handling

The gateway listens on multiple channels:

- **Wi‑Fi** for standard communication  
- **ESP‑NOW** for fallback and low‑latency events  
- **LoRa (future)** for long‑range redundancy  

It automatically prioritizes the most reliable channel.

---

## 🧠 Alert Logic

The gateway manages:

- vital sign alerts  
- trend‑based warnings  
- emergency button events  
- acknowledgment loops  
- escalation if no nurse responds  

---

## 📡 Future Cloud Integration

The gateway is designed to support:

- MQTT  
- REST endpoints  
- WebSocket streaming  
- ward dashboards  

Cloud integration is not part of v0.3 but is fully planned.

