<div align="center">

<pre>

   ██████╗  █████╗ ██████╗ ███████╗██╗     ██╗███╗   ██╗██╗  ██╗
  ██╔════╝ ██╔══██╗██╔══██╗██╔════╝██║     ██║████╗  ██║██║ ██╔╝
  ██║      ███████║██████╔╝█████╗  ██║     ██║██╔██╗ ██║█████╔╝ 
  ██║      ██╔══██║██╔══██╗██╔══╝  ██║     ██║██║╚██╗██║██╔═██╗ 
  ╚██████╗ ██║  ██║██║  ██║███████╗███████╗██║██║ ╚████║██║  ██╗
   ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚══════╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝

CARELINK • Connected Care Mesh  
Patient • Nurse • Gateway • Cloud‑Ready System
</pre>

</div>

---

# 🏥 CareLink Mesh System  
### *Born in the ward. Built for the ward. A tribute to those who care.*

![Version](https://img.shields.io/badge/Version-0.3--EN-blue)
![Platform](https://img.shields.io/badge/Platform-ESP8266--HW364A-orange)
![Framework](https://img.shields.io/badge/Framework-Arduino/PlatformIO-blue)
![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)

CareLink was not imagined in a lab.  
It was born in real hospital wards — during long shifts, beside patients who needed constant attention, and among professionals who carry the weight of care every single day.

This project does **not** aim to replace anyone.  
It exists to **support everyone**.

CareLink is a tribute to the entire healthcare team:

- nurses  
- healthcare assistant and support staff  
- physicians and residents  
- physiotherapists  
- rehabilitation and respiratory therapists  
- medical technicians  
- all professionals who make patient care possible  

Every one of them faces pressure, fatigue, responsibility, and moments where time is never enough.  
CareLink wants to give back a little of that time.

It aims to reduce stress, prevent oversights, and anticipate problems before they grow.  
It is designed to be a **silent ally**, a background presence that helps clinical work remain human, focused, and safe.

This project is my way of honoring the people I worked with for years —  
and also the path I am building for my own future, a bridge between healthcare and engineering.

---

# ✨ What’s New in v0.3 — *Configuration & Pairing Release*

CareLink v0.3 introduces the foundation that transforms the system from a prototype into a **deployable bedside device**.

### 🔗 Secure Pairing  
A new nurse‑first ESP‑NOW handshake allows each Patient Node to be paired with a specific Nurse Node.

### ⚙️ Persistent Configuration  
A Captive Portal now allows bedside setup of:
- **Bed ID**  
- **Nurse MAC Address**

Values are stored in EEPROM and survive reboots.

### 🌐 Captive Portal Setup  
On first boot (or after factory reset), the Patient Node exposes a Wi‑Fi AP for configuration.

### 🖥️ OLED Feedback  
Nodes now display:
- Setup Mode  
- Pairing in progress  
- Pairing successful  

### 🧩 Gateway Integration  
The gateway logs pairing events and prepares for clinical telemetry in v0.4.

---

# 🧱 Architecture Overview (v0.3)

CareLink now consists of:

- **Patient Node**  
  Configuration, EEPROM, pairing, OLED feedback.

- **Nurse Node**  
  Pairing validation, bedside association, OLED feedback.

- **Gateway**  
  Pairing event logging, future telemetry pipeline.

Documentation:

- `docs/pairing-flow.md`  
- `docs/configuration.md`  
- `docs/captive-portal.md`  
- `docs/architecture.md`

---

# 🛠️ Roadmap

- **v0.2 — Clinical Intelligence** *(completed)*  
- **v0.3 — Configuration & Pairing** *(current)*  
- **v0.4 — Clinical Telemetry** *(next)*  
- **v0.5 — Escalation & Doctor Node*  
- **v0.6 — Mesh Networking*  

---

# ❤️ A Project With a Soul

CareLink is not just technology.  
It is gratitude, experience, and hope — turned into a system.  
And it will keep growing, just as I do.

