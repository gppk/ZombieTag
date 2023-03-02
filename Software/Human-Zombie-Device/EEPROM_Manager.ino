#include "EEPROM_Manager.h"

DeviceState init_and_read_device_state(){

// This code works but i've commented it out to not nuke the EEPROM with lots of
// writes/reads whilst building the code. Also needs a tidy up/no magic numbers
//  EEPROM.begin(EEPROM_BYTE_SIZE);
//  // Read the existing device state from EEPROM
//  deviceState = (DeviceState)EEPROM.read(EEPROM_ADDRESS);

    return DeviceState::human;
}