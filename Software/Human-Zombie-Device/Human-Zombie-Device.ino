// add in this
// https://hackmd.io/@exradr/clang-format

// code for DOITESP32 DEVKIT V1

// Custom ZTag Libraries
#include "DeviceState.h"
#include "EEPROM_Manager.h"
#include "ArduinoBle_Manager.h"
#include "Oled_Manager.h"
#include "SerialHelper.h"

ArduinoBle_Manager bleManager;

void setup() {
    // initialize Serial Monitor
    Serial.begin(115200);

    init_oled();

    write_oled_line(1, "ZTAG DEVICE");
    Serial.println("ZTAG DEVICE");

    bleManager.initBleZTagDevice();
    Serial.println("Ble Initializing");

    // Get the saved state from EEPROM and output it
    deviceState = init_and_read_device_state();
    numberOfInfectionTicks = 0;   // set the infection counter to zero.
    write_oled_and_serial_line(2, DeviceStateToString(deviceState));

    bleManager.updateZtagBeaconName(DeviceStateToString(DeviceState::human));
    
}

void loop() {

    bleManager.pollBle(); 
    
    if (bleManager.getFoundZtagDevices().size() > 0) {
        // If we find a zTag device then store that in foundZTagData        
        Serial << "number of ZTags found: " << bleManager.getFoundZtagDevices().size() << '\n';
    }

    // Write some behaviour code, somewhere that isn't loop!

    // Then write some OLED Stats Update Code, probably somewhere that isn't loop!
    
}
