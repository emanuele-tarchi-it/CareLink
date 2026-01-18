#include <EEPROM.h>
#include "config.h"

CareLinkConfig config;

void loadConfig() {
    EEPROM.begin(512);
    EEPROM.get(0, config);

    if (config.bed_id[0] == '\0') {
        strcpy(config.bed_id, "UNSET");
        strcpy(config.nurse_mac, "00:00:00:00:00:00");
        config.paired = false;
    }
}

void saveConfig() {
    EEPROM.put(0, config);
    EEPROM.commit();
}

void resetConfig() {
    memset(&config, 0, sizeof(config));
    saveConfig();
}
