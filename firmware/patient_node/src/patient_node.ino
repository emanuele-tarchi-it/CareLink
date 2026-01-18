#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_MAX30205.h>

extern "C" {
  #include "algorithm.h"   // Algoritmo Maxim ufficiale
}

// --- Display ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- MAX30102 ---
#define MAX30102_ADDR 0x57

// --- Buffer per algoritmo Maxim ---
#define BUFFER_SIZE 100
uint32_t irBuffer[BUFFER_SIZE];
uint32_t redBuffer[BUFFER_SIZE];

// --- Risultati ---
int32_t spo2 = 0;
int8_t spo2Valid = 0;
int32_t heartRate = 0;
int8_t heartRateValid = 0;

// --- Temperatura ---
MAX30205 tempSensor;
float temperatureC = 0.0;
bool tempValid = false;

// --- Blink ---
unsigned long lastBlink = 0;
bool blinkState = false;

// --- Bed ID ---
String bed_id = "B12";

// --- Funzioni I2C MAX30102 ---
void max30102Write(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(MAX30102_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void max30102ReadFIFO(uint32_t *ir, uint32_t *red) {
    Wire.beginTransmission(MAX30102_ADDR);
    Wire.write(0x07);
    Wire.endTransmission(false);
    Wire.requestFrom(MAX30102_ADDR, (uint8_t)6);

    if (Wire.available() == 6) {
        uint32_t un_red = 0;
        uint32_t un_ir = 0;

        un_red |= (uint32_t)Wire.read() << 16;
        un_red |= (uint32_t)Wire.read() << 8;
        un_red |= (uint32_t)Wire.read();
        un_red &= 0x03FFFF;

        un_ir |= (uint32_t)Wire.read() << 16;
        un_ir |= (uint32_t)Wire.read() << 8;
        un_ir |= (uint32_t)Wire.read();
        un_ir &= 0x03FFFF;

        *red = un_red;
        *ir = un_ir;
    }
}

// --- Setup MAX30102 ---
void setupMAX30102() {
    max30102Write(0x09, 0x40);
    delay(100);

    max30102Write(0x02, 0x00);
    max30102Write(0x03, 0x00);

    max30102Write(0x08, 0x4F);
    max30102Write(0x09, 0x03);
    max30102Write(0x0A, 0x27);

    max30102Write(0x0C, 0x24);
    max30102Write(0x0D, 0x24);
}

// --- Shock Index ---
float computeShockIndex(int spo2, int bpm) {
    if (spo2 <= 0) return 0.0;
    return (float)bpm / (float)spo2;
}

// --- Infection Alert ---
bool checkInfectionAlert(float temp, int spo2, int bpm, float shockIndex) {
    if (temp > 39.0) return true;
    if (temp > 38.0 && bpm > 100) return true;
    if (temp > 38.0 && shockIndex > 1.0) return true;
    if (temp > 38.0 && spo2 < 94) return true;
    return false;
}

// --- Display ---
void showVitals(int spo2, int bpm, float shockIndex, float tempC,
                bool spo2Critical, bool shockCritical, bool tempCritical,
                bool infectionAlert) {

    bool critical = spo2Critical || shockCritical || tempCritical || infectionAlert;

    if (critical) {
        if (millis() - lastBlink > 300) {
            lastBlink = millis();
            blinkState = !blinkState;
            display.invertDisplay(blinkState);
        }
    } else {
        display.invertDisplay(false);
    }

    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Bed: ");
    display.print(bed_id);

    display.setTextSize(2);
    display.setCursor(0, 12);

    if (critical) {
        if (spo2Critical) {
            display.print("SpO2 ");
            display.print(spo2);
        } else if (shockCritical) {
            display.print("sSI ");
            display.print(shockIndex, 2);
        } else if (tempCritical || infectionAlert) {
            display.print("TEMP ");
            display.print(tempC, 1);
        }

        display.setTextSize(1);
        display.setCursor(0, 48);
        if (infectionAlert) display.print("INFECTION ALERT");
        else if (tempCritical) display.print("FEVER ALERT");
        else if (shockCritical) display.print("SHOCK ALERT");
        else if (spo2Critical) display.print("
