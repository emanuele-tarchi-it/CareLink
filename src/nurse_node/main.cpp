#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include "oled.h"

// -------------------------------
// PACKET STRUCTURES
// -------------------------------
typedef struct {
    char bed_id[8];
    uint8_t mac[6];
} PairingPacket;

typedef struct {
    uint8_t status;   // 1 = OK, 0 = FAIL
} PairingResponse;

// -------------------------------
// FORWARD DECLARATIONS
// -------------------------------
void initESPNow();
void onDataRecv(uint8_t *mac, uint8_t *data, uint8_t len);
void sendPairingResponse(uint8_t *mac, bool ok);

// -------------------------------
// SETUP
// -------------------------------
void setup() {
    Serial.begin(115200);
    oledInit();
    oledPrint("Nurse Node v0.3");

    WiFi.mode(WIFI_STA);

    initESPNow();
    oledPrint("Ready for pairing");
}

// -------------------------------
// LOOP
// -------------------------------
void loop() {
    // v0.3: no vitals yet
    delay(1000);
}

// -------------------------------
// ESP-NOW INIT
// -------------------------------
void initESPNow() {
    if (esp_now_init() != 0) {
        oledPrint("ESP-NOW FAIL");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(onDataRecv);
}

// -------------------------------
// RECEIVE PAIRING REQUEST
// -------------------------------
void onDataRecv(uint8_t *mac, uint8_t *data, uint8_t len) {
    if (len < sizeof(PairingPacket)) return;

    PairingPacket pkt;
    memcpy(&pkt, data, sizeof(pkt));

    Serial.println("Pairing request from:");
    Serial.printf("%02X:%02X:%02X:%02X:%02X:%02X\n",
                  mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    Serial.print("Bed: ");
    Serial.println(pkt.bed_id);

    // v0.3: accept all pairings
    bool ok = true;

    sendPairingResponse(mac, ok);

    if (ok) {
        oledPrint("Paired bed ");
        oledAppend(pkt.bed_id);
    }
}

// -------------------------------
// SEND PAIRING RESPONSE
// -------------------------------
void sendPairingResponse(uint8_t *mac, bool ok) {
    PairingResponse resp;
    resp.status = ok ? 1 : 0;

    esp_now_send(mac, (uint8_t*)&resp, sizeof(resp));
}

