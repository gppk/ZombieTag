#pragma once

//TODO: If these are to be configurable items they need to be in a struct not #defines
#define MIN_DETECTION_RSSI_STENGTH -70
#define NUM_OF_INFECT_HITS 3
#define HEALTH_REDUCTION 1
#define HEALTH_MAX 2
#define HEALTH_MIN 0

enum DeviceState {
    initialising,
    human,
    infected,
    medicalzone,
    null
};

struct HealthBar {
    uint health = HEALTH_MAX; // This is something that should probably live in EEPROM too... I think we need an EEPROM layout 
};

uint numberOfInfectionTicks;
HealthBar wearableHealth;

// deviceState set from EEPROM in setup
DeviceState deviceState;

const char* DeviceStateToString( DeviceState ds ) {
    switch ( ds )
    {
        case DeviceState::initialising: return "initialising";
        case DeviceState::human: return "human";
        case DeviceState::infected: return "infected";
        case DeviceState::medicalzone: return "medical zone";
        case DeviceState::null: return "null";
        default: return "Default";
    }
}

DeviceState StringToDeviceState (String s) {  
    if ( s == "initialising" ) return DeviceState::initialising;
    if ( s == "human" ) return DeviceState::human;
    if ( s == "infected" ) return DeviceState::infected;
    if ( s == "medical zone" ) return DeviceState::medicalzone;
    // else
    return DeviceState::null;
}

// Not sure if this deserves to be in here or Lora_Manager.h but probs here.
bool is_message_ztag ( String receivedLoraMessage ) {
    bool isZtag = false;

    if ( StringToDeviceState(receivedLoraMessage) != DeviceState::null ) {
        isZtag = true;
    }
    
    return isZtag;
}

// Main behaviour code for figuring out if we are infected yet. 
// Itll do the addition of a new infected message if its true and close
// This function handles going to the infected device state so its not outside this header.
void is_infected_yet(int rssi) {

    // Step 0
    // Some simple error handling, if we get here and we already have health of 0, just go straight to infected and return
    if (wearableHealth.health == 0) {
        deviceState = DeviceState::infected;
        return;
    }
    
    // Step 1, check the RSSI
    // remember its negative so a lower number is a weaker signal strength. 0 is a very very high strength.
    if (rssi < MIN_DETECTION_RSSI_STENGTH) {
        Serial.println("RSSI Doesn't minimum detection criteria");
        return; // Just leave, infected isn't close enough to effect our state
    }
    
    Serial.println("RSSI meets minimum detection criteria");
    
    // Step 3 - Add an infection tick
    // The number of infection ticks needs to hit NUM_OF_INFECT_HITS before taking HEALTH_REDUCTION level off the health bar
    // when the health bar reaches 0, you are infected.
    if (++numberOfInfectionTicks == NUM_OF_INFECT_HITS) {
        wearableHealth.health--;
        numberOfInfectionTicks = 0; // reset the tick count
    }

    // Step 4 - Check the health\
    // basically if 0 go to infected, but i added a #define in case it for some reason becomes not 0...
    if (wearableHealth.health == HEALTH_MIN) {
        deviceState = DeviceState::infected;
    }
}

void reset_infection_ticker() {
    numberOfInfectionTicks = 0;
}
void reset_health() {
    wearableHealth.health = HEALTH_MAX;
}