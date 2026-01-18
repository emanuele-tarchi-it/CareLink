# 🔗 CareLink Pairing Flow — v0.3
### *Secure bedside pairing between Patient Node and Nurse Node*

CareLink v0.3 introduces a simple, safe, nurse-first pairing mechanism that allows each Patient Node to be assigned to a specific Nurse Node and bed identity.

## 1. Bed Identity Assignment
Each Patient Node receives:
- `bed_id`
- `nurse_mac`

These values are configured via Captive Portal and stored in EEPROM.

## 2. Pairing Handshake
When the Patient Node boots:
1. Loads `bed_id` and `nurse_mac`
2. Sends a pairing request to the Nurse Node
3. Nurse Node validates:
   - MAC address
   - bed assignment
4. Nurse Node replies with confirmation
5. OLED displays: **“Paired with Nurse Node”**

## 3. Safety Principles
- No automatic pairing
- No broadcast pairing
- Nurse-first validation
- Persistent storage with fallback defaults
