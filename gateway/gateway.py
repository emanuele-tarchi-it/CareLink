#!/usr/bin/env python3
# CareLink Gateway v0.3
# Handles pairing events and prepares for telemetry (v0.4)

import serial
import json
import time

SERIAL_PORT = "/dev/ttyUSB0"
BAUD_RATE = 115200

def log(msg):
    ts = time.strftime("%Y-%m-%d %H:%M:%S")
    print(f"[{ts}] {msg}")

def parse_pairing_event(raw):
    """
    v0.3 pairing packet structure:
    {
        "event": "pairing",
        "bed_id": "B12",
        "mac": "AA:BB:CC:DD:EE:FF",
        "status": 1
    }
    """
    try:
        data = json.loads(raw)
        if data.get("event") == "pairing":
            return data
    except:
        return None

def handle_pairing(event):
    bed = event.get("bed_id", "UNKNOWN")
    mac = event.get("mac", "??:??:??:??:??:??")
    status = event.get("status", 0)

    if status == 1:
        log(f"PAIRING OK — Bed {bed} paired with {mac}")
    else:
        log(f"PAIRING FAIL — Bed {bed} rejected for {mac}")

def main():
    log("CareLink Gateway v0.3 starting...")
    log("Waiting for pairing events...")

    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    except Exception as e:
        log(f"Serial error: {e}")
        return

    while True:
        raw = ser.readline().decode("utf-8").strip()
        if not raw:
            continue

        event = parse_pairing_event(raw)
        if event:
            handle_pairing(event)
        else:
            # v0.3: ignore non-pairing data
            pass

if __name__ == "__main__":
    main()
