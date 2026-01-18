#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include "config.h"
#include "captive_portal.h"
#include "storage.h"
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
void sendPairingRequest();
void onDataRecv(uint8_t *mac, uint8_t *data, uint8_t len);

// -------------------------------
// SETUP
// -------------------------------
void setup() {
    Serial.begin(115200);
    oledInit();
    oledPrint("Booting...");

    loadConfig();

    // If configuration missing → start Captive Portal
    if (strcmp(config.bed_id, "UNSET") == 0) {
        oledPrint("Setup Mode");
        startCaptivePortal();
        return;
    }

    oledPrint("Loading config...");
    delay(500);

    // Initialize ESP-NOW
    initESPNow();

    // Start pairing if not paired
    if (!config.paired) {
        oledPrint("Pairing...");
        sendPairingRequest();
    } else {
        oledPrint("Paired ✓");
    }
}

// -------------------------------
// LOOP
// -------------------------------
void loop() {
    // In v0.3 the Patient Node only:
    // - stays paired
    // - monitors vitals (v0.4+)
    // - sends alerts (v0.4+)
    delay(1000);
}

// -------------------------------
// ESP-NOW INITIALIZATION
// -------------------------------
void initESPNow() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0) {
        Serial.println("ESP-NOW init failed");
        oledPrint("ESP-NOW FAIL");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_register_recv_cb(onDataRecv);

    // Convert nurse MAC string → bytes
    uint8_t nurseMac[6];
    sscanf(config.nurse_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &nurseMac[0], &nurseMac[1], &nurseMac[2],
           &nurseMac[3], &nurseMac[4], &nurseMac[5]);

    esp_now_add_peer(nurseMac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

// -------------------------------
// SEND PAIRING REQUEST
// -------------------------------
void sendPairingRequest() {
    PairingPacket pkt;
    strcpy(pkt.bed_id, config.bed_id);
    WiFi.macAddress(pkt.mac);

    uint8_t nurseMac[6];
    sscanf(config.nurse_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &nurseMac[0], &nurseMac[1], &nurseMac[2],
           &nurseMac[3], &nurseMac[4], &nurseMac[5]);

    esp_now_send(nurseMac, (uint8_t*)&pkt, sizeof(pkt));
    Serial.println("Pairing request sent");
}

// -------------------------------
// RECEIVE PAIRING RESPONSE
// -------------------------------
void onDataRecv(uint8_t *mac, uint8_t *data, uint8_t len) {
    if (len < 1) return;

    PairingResponse *resp = (PairingResponse*)data;

    if (resp->status == 1) {
        oledPrint("Paired ✓");
        config.paired = true;
        saveConfig();
        Serial.println("Pairing OK");
    } else {
        oledPrint("Pairing FAIL");
        Serial.println("Pairing failed");
    }
}
