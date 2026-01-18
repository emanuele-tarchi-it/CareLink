import struct
import serial
import json
import yaml
import time
from datetime import datetime

# Carica configurazione da YAML
with open("config.yaml", "r") as f:
    config = yaml.safe_load(f)

# Formato della Struct C (carelink_msg_t):
# <  : Little Endian
# 4s : char[4] (bed_id)
# I  : uint32_t (timestamp)
# B  : uint8_t (alert_type)
# H  : uint16_t (bpm)
# B  : uint8_t (spo2)
# f  : float (temperature)
# f  : float (shock_index)
STRUCT_FORMAT = "<4sIBHBff"
STRUCT_SIZE = struct.calcsize(STRUCT_FORMAT) # Dovrebbe essere 21

def log_event(event_type: str, data: dict):
    """Log event to file in JSON format."""
    log_entry = {
        "event": event_type,
        "timestamp": datetime.now().isoformat(),
        "data": data
    }
    with open(config['logging']['filename'], "a") as f:
        f.write(json.dumps(log_entry) + "\n")

def parse_binary_packet(raw_data):
    """Converte i byte grezzi nella struct CareLink."""
    try:
        unpacked = struct.unpack(STRUCT_FORMAT, raw_data)
        return {
            "bed_id": unpacked[0].decode('utf-8').strip('\x00'),
            "uptime_ms": unpacked[1],
            "alert_type": unpacked[2],
            "bpm": unpacked[3],
            "spo2": unpacked[4],
            "temp": round(unpacked[5], 2),
            "shock_index": round(unpacked[6], 2)
        }
    except Exception as e:
        print(f"❌ Parsing error: {e}")
        return None

def main():
    print(f"=== CareLink Mesh Gateway v0.2 ===")
    print(f"Connecting to {config['serial']['port']} at {config['serial']['baudrate']}...")
    
    try:
        ser = serial.Serial(
            port=config['serial']['port'],
            baudrate=config['serial']['baudrate'],
            timeout=config['serial']['timeout']
        )
    except Exception as e:
        print(f"❌ Serial Connection Error: {e}")
        return

    print("📡 Monitoring Clinical Data...\n")

    while True:
        # Cerca l'inizio di un pacchetto (si può ottimizzare con un header se necessario)
        if ser.in_waiting >= STRUCT_SIZE:
            raw_data = ser.read(STRUCT_SIZE)
            data = parse_binary_packet(raw_data)
            
            if data:
                # Mappatura tipi allarme
                alert_labels = ["NORM", "SOS", "INFECTION", "SHOCK"]
                label = alert_labels[data['alert_type']] if data['alert_type'] < 4 else "UNKNOWN"
                
                print(f"📩 [{datetime.now().strftime('%H:%M:%S')}] Bed {data['bed_id']} | Type: {label}")
                print(f"   HR: {data['bpm']} | SpO2: {data['spo2']}% | Temp: {data['temp']}°C | sSI: {data['shock_index']}")
                
                # Log del dato clinico
                log_event("DATA_RECEIVED", data)
                
                # Se è un allarme critico, stampa un alert visivo
                if data['alert_type'] > 0:
                    print(f"⚠️  CRITICAL ALERT: {label} on Bed {data['bed_id']}!")
        
        time.sleep(0.01) # Riduce carico CPU

if __name__ == "__main__":
    main()
