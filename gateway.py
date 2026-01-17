import json
import time
from datetime import datetime

LOG_FILE = "gateway_log.txt"

def log_event(event: dict):
    """Append event to local log file."""
    with open(LOG_FILE, "a") as f:
        f.write(json.dumps(event) + "\n")

def validate_message(msg: dict) -> bool:
    """Basic validation according to protocol."""
    required_fields = ["type", "node_id", "timestamp", "payload"]
    return all(field in msg for field in required_fields)

def create_ack(original_msg: dict) -> dict:
    """Generate ACK message."""
    return {
        "type": "ACK",
        "node_id": "gateway_01",
        "timestamp": int(time.time() * 1000),
        "payload": {
            "alert_id": f"{original_msg['node_id']}_{original_msg['timestamp']}",
            "status": "ACKNOWLEDGED"
        }
    }

def process_message(raw: str):
    """Process incoming raw JSON message."""
    try:
        msg = json.loads(raw)
    except json.JSONDecodeError:
        print("❌ Invalid JSON received")
        return

    if not validate_message(msg):
        print("❌ Message missing required fields")
        return

    print(f"📩 Received: {msg['type']} from {msg['node_id']}")

    # Log the message
    log_event({
        "event": "RECEIVED",
        "data": msg,
        "timestamp": datetime.now().isoformat()
    })

    # Handle message types
    if msg["type"] == "ALERT":
        print("⚠️  Alert received, generating ACK...")
        ack = create_ack(msg)
        print("📤 ACK:", ack)

        log_event({
            "event": "ACK_SENT",
            "data": ack,
            "timestamp": datetime.now().isoformat()
        })

    elif msg["type"] == "HELP":
        print("🚨 HELP request received!")
        log_event({
            "event": "HELP_RECEIVED",
            "data": msg,
            "timestamp": datetime.now().isoformat()
        })

    elif msg["type"] == "STATUS":
        print("📡 Status update received")
        log_event({
            "event": "STATUS_UPDATE",
            "data": msg,
            "timestamp": datetime.now().isoformat()
        })

    else:
        print("ℹ️ Unknown message type")
        log_event({
            "event": "UNKNOWN_TYPE",
            "data": msg,
            "timestamp": datetime.now().isoformat()
        })

def main():
    print("=== CareLink Mesh System — Python Gateway v0.1 ===")
    print("Waiting for messages...\n")

    while True:
        raw = input("Paste JSON message: ")
        process_message(raw)
        print()

if __name__ == "__main__":
    main()
