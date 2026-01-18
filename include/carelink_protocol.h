/**
 * @file carelink_protocol.h
 * @author CareLink Team
 * @brief Binary protocol definition v0.2 for ESP-NOW.
 *        This file defines the packet structure to ensure consistency
 *        across Patient, Nurse, and Gateway nodes.
 */

#ifndef CARELINK_PROTOCOL_H
#define CARELINK_PROTOCOL_H

#include <Arduino.h>

// Alert type definitions (alert_type)
#define ALERT_NORM      0x00  // Normal state, routine telemetry
#define ALERT_SOS       0x01  // Manual emergency call
#define ALERT_INFECTION 0x02  // Clinical alert: Fever + Tachycardia
#define ALERT_SHOCK     0x03  // Clinical alert: Shock Index > 1.0

/**
 * @struct carelink_msg_t
 * @brief Binary message structure (21 bytes total)
 *        The 'packed' attribute prevents the compiler from adding padding,
 *        which is essential for P2P transmission across different architectures.
 */
typedef struct __attribute__((packed)) {
    char bed_id[4];         // Bed ID (e.g., "B12\0")
    uint32_t timestamp;     // Node uptime or Epoch time (seconds)
    uint8_t alert_type;     // Alert code (0–3)
    uint16_t bpm;           // Heart rate (Beats Per Minute)
    uint8_t spo2;           // Oxygen saturation (0–100%)
    float temperature;      // Body temperature (°C)
    float shock_index;      // Calculated as BPM / SpO2
} carelink_msg_t;

// ACK byte for ESP-NOW acknowledgment
#define CARELINK_ACK_BYTE 0x06

#endif // CARELINK_PROTOCOL_H
