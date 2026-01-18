# 📡 CareLink Mesh System — Communication Protocol
> **Binary-Optimized Protocol for Resilient Clinical Telemetry & Device Pairing**

This document defines the binary communication standards for the CareLink Mesh System. It covers both the **Telemetry Layer (v0.2)** for vital signs and the **Pairing Layer (v0.3)** for device association.

---

## 🟦 PART I: Clinical Telemetry (v0.2)
*Optimized for low latency and minimal power consumption on ESP8266/ESP32 hardware.*

### 1. 📦 Message Structure (Binary Payload)
To maximize performance, messages are transmitted as raw byte arrays mapped directly to a C-structure. This avoids the overhead of JSON parsing.

**C-Struct Definition:**
    typedef struct __attribute__((packed)) {
        char bed_id[4];         // Unit identifier (e.g., "B12")
        uint32_t timestamp;     // Relative uptime or Epoch ms
        uint8_t alert_type;     // 0: NORM, 1: SOS, 2: INFECTION, 3: SHOCK
        uint16_t bpm;           // Heart Rate (BPM)
        uint8_t spo2;           // Oxygen Saturation (%)
        float temperature;      // Body Temperature (°C)
        float shock_index;      // Calculated sSI (BPM/SpO2)
    } carelink_msg_t;

### 2. 🚦 Alert Classification & Priority
The protocol implements edge-calculated priority levels. Each alert_type triggers specific behaviors on both Patient and Nurse nodes:

| Alert Code | Severity | Description | Trigger Condition |
|:--- | :--- | :--- | :--- |
| **0x00 (NORM)** | Low | Routine Telemetry | Vitals within safe thresholds. |
| **0x01 (SOS)** | Critical | Manual Alert | Emergency button pressed by patient. |
| **0x02 (INFECT)** | High | Infection Risk | Temp > 38.0°C + Tachycardia (BPM > 100). |
| **0x03 (SHOCK)** | Critical | Hemodynamic Alert | sSI > 1.0 (BPM/SpO2 ratio). |

### 3. 📶 Communication Fallback Strategy
CareLink enforces a tiered transmission logic to guarantee delivery:
1. Wi-Fi (Primary): Uses MQTT/TCP for long-term data logging at the Gateway.
2. ESP-NOW (Secondary): Fast, peer-to-peer failover if the local Wi-Fi router is down.
3. LoRa Mesh (Future): Emergency long-range layer for total building power failure.

### 4. 🔄 Acknowledgment (ACK) & Retries
1. Broadcast: Patient Node sends carelink_msg_t.
2. ACK: Nurse Node replies with a 1-byte confirmation (0x06) to the sender's MAC.
3. Timeout: If no ACK arrives within 500ms, the Patient Node retries up to 3 times.
4. Escalation: If retries fail, the node enters "Isolated Alert Mode" (OLED Flashing).

---

## 🟧 PART II: Pairing & Identity (v0.3)
*Nurse-First ESP-NOW Handshake for Secure Bedside Association.*

### 5. 📡 Pairing Request Packet (Patient → Nurse)
The Patient Node sends this request immediately after boot or factory reset.

**C-Struct Definition:**
    typedef struct __attribute__((packed)) {
        char bed_id[8];     // Configured Bed ID (e.g., "B12")
        uint8_t mac[6];     // Patient Node MAC address
    } PairingPacket;

### 6. 📩 Pairing Response Packet (Nurse → Patient)
The Nurse Node replies to authorize or reject the association.

**C-Struct Definition:**
    typedef struct __attribute__((packed)) {
        uint8_t status;     // 1 = Accepted, 0 = Rejected
    } PairingResponse;

### 7. 🔄 Pairing Flow Summary
1. Boot: Patient Node loads configuration from EEPROM.
2. Discovery: If not paired, it broadcasts a PairingPacket.
3. Validation: Nurse Node receives the request (v0.3: auto-accept).
4. Handshake: Nurse Node replies with PairingResponse (status = 1).
5. Persistence: Patient Node stores the Nurse MAC in EEPROM and enters "Paired State".

---

## 🛠️ Implementation & Hardware (HW-364A)

### 8. 🚨 Visual Urgency Protocol
* Standby: OLED displays real-time vitals and bed_id.
* Critical/Unacknowledged: The system calls display.invertDisplay(true) at 300ms intervals, creating a high-contrast strobe effect.

### 9. ⚙️ Technical Notes
* Memory Footprint: Telemetry packet is exactly 21 bytes.
* Bus Timing: Sensor polling (MAX30102/MAX30205) is interleaved with radio bursts to prevent I2C bus jitter on GPIO 14 (SDA) and GPIO 12 (SCL).
* Separation of Concerns: Pairing is isolated from telemetry to ensure identity is established before clinical algorithms start.

---

## ⚠️ Disclaimer
*CareLink Mesh System is a technical and educational prototype. It is not a certified medical device and should not be used for life-critical monitoring.*