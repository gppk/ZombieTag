#include "DeviceState.h"

const char* DeviceStateToString( enum DeviceState ds ) {
    switch ( ds )
    {
        case DeviceState::initialising:
            return "initialising";
        case DeviceState::human: 
            return "human";
        case DeviceState::infected: 
            return "infected";
        case DeviceState::medicalzone: 
            return "medical zone";
        case DeviceState::null:
            return "null";
        default: 
            return "Default";
    }
}

enum DeviceState StringToDeviceState (String s) {  
    if ( s == "initialising" ) 
        return DeviceState::initialising;
    else if( s == "human" ) return DeviceState::human;
    if ( s == "infected" ) return DeviceState::infected;
    if ( s == "medical zone" ) return DeviceState::medicalzone;
    // else
    return DeviceState::null;
}

// Not sure if this deserves to be in here or Lora_Manager.h but probs here.
bool is_message_ztag ( String recievedLoraMessage ) {
    bool isZtag = false;

    if ( StringToDeviceState(recievedLoraMessage) != DeviceState::null ) {
        isZtag = true;
    }
    
    return isZtag;
}
