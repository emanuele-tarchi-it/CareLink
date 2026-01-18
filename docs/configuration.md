# ⚙️ CareLink Configuration — v0.3

CareLink v0.3 introduces persistent configuration for each Patient Node.

## Stored Parameters
- `bed_id`
- `nurse_mac`
- Wi-Fi credentials (optional)
- pairing status

## Storage
Values are stored in EEPROM with:
- corruption check
- default fallback
- factory reset (long-press button)

## Reset Procedure
Hold the reset button for **5 seconds**:
- clears EEPROM
- restarts Captive Portal
