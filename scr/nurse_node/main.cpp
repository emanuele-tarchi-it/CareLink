#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Header condiviso del protocollo
#include "carelink_protocol.h"

// --- Configurazione Display (HW-364A) ---
#define I2C_SDA 14
#define I2C_SCL 12
Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Struttura locale per i dati in arrivo
carelink_msg_t incomingData;

// --- Callback di ricezione ESP-NOW ---
void onDataRecv(uint8_t * mac, uint8_t *incomingRaw, uint8_t len) {
    // 1. Verifica dimensione pacchetto (v0.2 = 21 byte)
    if (len != sizeof(carelink_msg_t)) return;

    // 2. Copia i byte nella struct locale
    memcpy(&incomingData, incomingRaw, sizeof(incomingData));

    // 3. Inoltro binario verso il Gateway Python (Serial)
    // Inviamo i byte grezzi; il gateway.py userà struct.unpack
    Serial.write((uint8_t *)&incomingData, sizeof(incomingData));

    // 4. Feedback Visivo sul Display
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Bed: "); display.println(incomingData.bed_id);
    
    display.setTextSize(2);
    display.print("HR:  "); display.println(incomingData.bpm);
    display.print("SpO2:"); display.print(incomingData.spo2); display.println("%");
    
    if(incomingData.alert_type > 0) {
        display.setCursor(0, 50);
        display.setTextSize(1);
        display.print("!!! ALERT DETECTED !!!");
        display.invertDisplay(true);
    } else {
        display.invertDisplay(false);
    }
    display.display();
}

void setup() {
    // La velocità deve corrispondere a quella nel config.yaml del gateway
    Serial.begin(115200);

    // Inizializzazione I2C e Display
    Wire.begin(I2C_SDA, I2C_SCL);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        for(;;); // Blocco se OLED non risponde
    }
    
    display.clearDisplay();
    display.setCursor(0,10);
    display.println("CareLink Nurse Node");
    display.println("v0.2 - Listening...");
    display.display();

    // Inizializzazione ESP-NOW
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Configurazione Ruolo e Callback
    esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
    esp_now_register_recv_cb(onDataRecv);
}

void loop() {
    // Il Nurse Node è guidato dagli interrupt (callback)
    // Qui si possono aggiungere funzioni di gestione locale (pulsanti per silenziare)
    delay(100);
}
