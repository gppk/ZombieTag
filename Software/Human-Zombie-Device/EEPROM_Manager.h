#include "DeviceState.h"
// Libraries & setup for data persistence
#include <EEPROM.h>
#define EEPROM_ADDRESS   0
#define EEPROM_BYTE_SIZE 1   // the number of bytes accessed

DeviceState init_and_read_device_state();