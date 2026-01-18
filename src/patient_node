#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_MAX30205.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

// I nostri header personalizzati
#include "algorithm.h"
#include "carelink_protocol.h"

// --- Configurazione I2C Specifica HW-364A ---
#define I2C_SDA 14
#define I2C_SCL 12

// --- Display & Sensori ---
Adafruit_SSD1306 display(128, 64, &Wire, -1);
MAX30205 tempSensor;
carelink_msg_t myData; // La struct definita in carelink_protocol.h

// --- Buffer Algoritmo ---
uint32_t irBuffer[100];
uint32_t redBuffer[100];
int32_t n_spo2, n_heart_rate;
int8_t b_spo2_valid, b_hr_valid;

// --- Indirizzo MAC del Nurse Node (da configurare nella v0.3) ---
uint8_t nurseAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Broadcast per ora

void setup() {
    Serial.begin(115200);
    
    // Inizializzazione I2C con pin corretti per HW-364A
    Wire.begin(I2C_SDA, I2C_SCL);

    // Inizializzazione Display
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println("OLED failed"); 
    }
    display.clearDisplay();
    display.display();

    // Inizializzazione ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != 0) {
        Serial.println("ESP-NOW failed");
    }
    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_add_peer(nurseAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

    // Configurazione MAX30205 e MAX30102 (qui useresti le tue funzioni setupMAX30102)
    tempSensor.begin();
    // [Inserire qui le tue funzioni max30102Write per config]

    // Prepariamo i dati statici della struct
    strcpy(myData.bed_id, "B12");
}

void loop() {
    // 1. Raccogli 100 campioni (circa 4 secondi a 25Hz)
    for (int i = 0; i < 100; i++) {
        // Leggi FIFO dal MAX30102 e riempi irBuffer[i] e redBuffer[i]
        // [Inserire qui la tua funzione max30102ReadFIFO]
        delay(40); // 25Hz
    }

    // 2. Esegui Algoritmo Maxim
    maxim_heart_rate_and_oxygen_saturation(irBuffer, 100, redBuffer, &n_spo2, &b_spo2_valid, &n_heart_rate, &b_hr_valid);

    // 3. Popola la struct CareLink v0.2
    myData.timestamp = millis();
    myData.bpm = (b_hr_valid) ? (uint16_t)n_heart_rate : 0;
    myData.spo2 = (b_spo2_valid) ? (uint8_t)n_spo2 : 0;
    myData.temperature = tempSensor.getTemperature();
    myData.shock_index = (myData.spo2 > 0) ? (float)myData.bpm / myData.spo2 : 0;

    // 4. Logica Allarmi Clinici
    if (myData.shock_index > 1.0) myData.alert_type = ALERT_SHOCK;
    else if (myData.temperature > 38.0 && myData.bpm > 100) myData.alert_type = ALERT_INFECTION;
    else myData.alert_type = ALERT_NORM;

    // 5. Invia al Gateway/Nurse via ESP-NOW
    esp_now_send(nurseAddress, (uint8_t *) &myData, sizeof(myData));

    // 6. Aggiorna Display (usando la tua funzione showVitals adattata alla struct)
    // showVitals(myData);
}
