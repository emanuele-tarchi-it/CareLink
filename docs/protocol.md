# CareLink Mesh System — Communication Protocol

This document defines the communication protocol used by Patient Nodes, Nurse Nodes, and the Gateway within the CareLink Mesh System.  
It specifies message formats, required fields, acknowledgment logic, retry behavior, and fallback rules across Wi‑Fi, ESP‑NOW, and LoRa.

---

## 1. Overview

The protocol is designed to be:

- **Lightweight** — suitable for ESP8266/ESP32 devices  
- **Deterministic** — predictable behavior in clinical workflows  
- **Resilient** — supports fallback channels and retries  
- **Extensible** — future‑proof for additional message types or cloud integration  

All messages follow a structured JSON‑like format (serialized as compact strings for ESP‑NOW and LoRa).

---

## 2. Message Types

The system defines the following core message types:

| Type | Description |
|------|-------------|
| `ALERT` | Sent by Patient Nodes when a threshold is exceeded or a manual alert is triggered |
| `ACK` | Sent by Nurse Nodes or Gateway to confirm receipt of an alert |
| `HELP` | Emergency assistance request from a Nurse Node |
| `SYNC` | Configuration or status synchronization from Gateway |
| `STATUS` | Periodic heartbeat from nodes |
| `ERROR` | Error or failure notification |

---

## 3. Message Format

All messages share a common structure:

{
“type”: “<MESSAGE_TYPE>”,
“node_id”: “<unique_node_id>”,
“timestamp”: <unix_epoch_ms>,
“payload”: { … }
}


### 3.1 Required Fields

- **type** — one of the defined message types  
- **node_id** — unique identifier for the sending node  
- **timestamp** — milliseconds since epoch  
- **payload** — message‑specific data  

---

## 4. Message Definitions

### 4.1 ALERT

Sent by Patient Nodes.

{
“type”: “ALERT”,
“node_id”: “patient_12”,
“timestamp”: 1737220000000,
“payload”: {
“bed_id”: “B12”,
“alert_code”: “LOW_SPO2”,
“value”: 86,
“priority”: “HIGH”
}
}


### 4.2 ACK

Sent by Nurse Nodes or Gateway.

{
“type”: “ACK”,
“node_id”: “nurse_03”,
“timestamp”: 1737220012000,
“payload”: {
“alert_id”: “patient_12_1737220000000”,
“operator_id”: “NURSE_03”,
“status”: “ACKNOWLEDGED”
}
}


### 4.3 HELP

Emergency request from a Nurse Node.

{
“type”: “HELP”,
“node_id”: “nurse_03”,
“timestamp”: 1737220025000,
“payload”: {
“location”: “Room 4”,
“reason”: “ASSISTANCE_REQUEST”
}
}


### 4.4 SYNC

Sent by Gateway to update configuration.

{
“type”: “SYNC”,
“node_id”: “gateway_01”,
“timestamp”: 1737220030000,
“payload”: {
“ward_id”: “WARD_A”,
“config_version”: 4,
“nodes”: {
“patient_12”: { “bed_id”: “B12” },
“nurse_03”: { “assigned_sector”: “A1” }
}
}
}


### 4.5 STATUS

Periodic heartbeat.

{
“type”: “STATUS”,
“node_id”: “patient_12”,
“timestamp”: 1737220040000,
“payload”: {
“battery”: 92,
“wifi”: “OK”,
“esp_now”: “READY”,
“lora”: “DISABLED”
}
}


---

## 5. Acknowledgment Logic

### 5.1 ALERT → ACK Flow

1. Patient Node sends `ALERT`
2. Nurse Node or Gateway receives it
3. Receiver sends `ACK`
4. Patient Node marks alert as delivered

### 5.2 Timeout & Retry

- If no ACK is received within **500 ms**, retry  
- Maximum retries: **3**  
- After 3 failures → fallback to next communication layer  

---

## 6. Fallback Strategy

### 6.1 Priority Order

1. **Wi‑Fi**  
2. **ESP‑NOW**  
3. **LoRa Mesh** (future)

### 6.2 Conditions for Fallback

| Condition | Action |
|----------|--------|
| Wi‑Fi unreachable | Switch to ESP‑NOW |
| ESP‑NOW unreachable | Switch to LoRa |
| Gateway unreachable | Attempt multi‑hop (ESP‑NOW or LoRa) |
| No path available | Store message locally and retry periodically |

---

## 7. Multi‑Hop Forwarding (Planned)

Nodes may forward messages when the Gateway is out of range.

### 7.1 Routing Rules (planned)

- Each node maintains a list of nearby nodes  
- Messages include a `hop_count` field  
- Maximum hops: **3**  
- Nodes drop messages if:  
  - hop_count exceeds max  
  - message ID already seen (loop prevention)

---

## 8. Message Security (Future Work)

Planned enhancements:

- Lightweight encryption (AES‑128)  
- Message signing (HMAC)  
- Replay protection (nonce + timestamp)  
- Role‑based permissions for SYNC messages  

---

## 9. Error Handling

Nodes may send `ERROR` messages when:

- sensor failure  
- communication failure  
- invalid configuration  
- repeated ACK timeout  

Example:

{
“type”: “ERROR”,
“node_id”: “patient_12”,
“timestamp”: 1737220055000,
“payload”: {
“code”: “SENSOR_FAILURE”,
“details”: “SPO2 sensor not responding”
}
}


---

## 10. Compatibility & Extensibility

The protocol is designed to:

- support new message types  
- evolve with cloud integration  
- remain lightweight for constrained devices  
- operate across heterogeneous communication layers  

---

## Disclaimer

This protocol is part of a technical and educational prototype.  
It is not intended for certified medical use.
