#pragma once

enum DeviceState {
    initialising,
    human,
    infected,
    medicalzone
};

const char* DeviceStateToString( DeviceState ds ) {
    switch ( ds )
    {
        case DeviceState::initialising: return "initialising";
        case DeviceState::human: return "human";
        case DeviceState::infected: return "infected";
        case DeviceState::medicalzone: return "medical zone";
        default: return "Default";
    }
}

DeviceState StringToDeviceState (String s) {  
    if ( s == "initialising" ) return DeviceState::initialising;
    if ( s == "human" ) return DeviceState::human;
    if ( s == "infected" ) return DeviceState::infected;
    if ( s == "medical zone" ) return DeviceState::medicalzone;
}