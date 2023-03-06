#ifndef DEVICE_STATE_H
#define DEVICE_STATE_H

#include <Arduino.h>
#include <cstring>
#include <stdbool.h>
#include <string.h>

// TODO: If these are to be configurable items they need to be in a struct not
// #defines
#define MIN_DETECTION_RSSI_STENGTH (-70)
#define NUM_OF_INFECT_HITS         (3)
#define HEALTH_REDUCTION           (1)
#define HEALTH_MAX                 (2)
#define HEALTH_MIN                 (0)

struct HealthBar {
    uint health =
        HEALTH_MAX;   // This is something that should probably live in EEPROM
                      // too... I think we need an EEPROM layout
};

extern uint numberOfInfectionTicks;
extern HealthBar wearableHealth;

enum DeviceState { initialising, human, infected, medicalzone, null };

// deviceState set from EEPROM in setup
extern DeviceState deviceState;

const char *DeviceStateToString(enum DeviceState ds);

enum DeviceState StringToDeviceState(String s);

// Not sure if this deserves to be in here or Lora_Manager.h but probs here.
bool is_message_ztag(String receivedLoraMessage);

void is_infected_yet(int rssi);

void reset_infection_ticker();

void reset_health();

#endif
