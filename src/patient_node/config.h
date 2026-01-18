#pragma once

struct CareLinkConfig {
    char bed_id[8];
    char nurse_mac[18];
    bool paired;
};

extern CareLinkConfig config;

void loadConfig();
void saveConfig();
void resetConfig();
