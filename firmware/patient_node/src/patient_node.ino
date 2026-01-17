#include <Arduino.h>
#include <ArduinoJson.h>

const int BUTTON_PIN = D3;   // Pulsante per simulare ALERT
unsigned long lastStatus = 0;

String createAlert() {
    StaticJsonDocument<256> doc;

    doc["type"] = "ALERT";
    doc["node_id"] = "patient_01";
    doc["timestamp"] = millis();

    JsonObject payload = doc.createNestedObject("payload");
    payload["bed_id"] = "B12";
    payload["alert_code"] = "TEST_ALERT";
    payload["value"] = 1;
    payload["priority"] = "HIGH";

    String output;
    serializeJson(doc, output);
    return output;
}

String createStatus() {
    StaticJsonDocument<256> doc;

    doc["type"] = "STATUS";
    doc["node_id"] = "patient_01";
    doc["timestamp"] = millis();

    JsonObject payload = doc.createNestedObject("payload");
    payload["battery"] = 98;
    payload["signal"] = -60;

    String output;
    serializeJson(doc, output);
    return output;
}

void setup() {
    Serial.begin(115200);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.println("=== CareLink Patient Node v0.1 ===");
    Serial.println("Premi il pulsante per inviare un ALERT");
    Serial.println("STATUS inviato ogni 10 secondi\n");
}

void loop() {
    // ALERT manuale
    if (digitalRead(BUTTON_PIN) == LOW) {
        delay(200); // debounce
        String alertMsg = createAlert();
        Serial.println(alertMsg);
        Serial.println();
    }

    // STATUS periodico
    if (millis() - lastStatus > 10000) {
        lastStatus = millis();
        String statusMsg = createStatus();
        Serial.println(statusMsg);
        Serial.println();
    }
}
