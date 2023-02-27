#include "DeviceState.h"

//Libraries & setup for data persistence
#include <EEPROM.h>
#define EEPROM_ADDRESS 0
#define EEPROM_BYTE_SIZE 1 //the number of bytes accessed

DeviceState init_and_read_device_state() {

// This code works but i've commented it out to not nuke the EEPROM with lots of
// writes/reads whilst building the code. Also needs a tidy up/no magic numbers
//  EEPROM.begin(EEPROM_BYTE_SIZE);
//  // Read the existing device state from EEPROM
//  deviceState = (DeviceState)EEPROM.read(0);

    return DeviceState::human;
}