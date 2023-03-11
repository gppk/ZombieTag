// add in this
// https://hackmd.io/@exradr/clang-format

// code for DOITESP32 DEVKIT V1

// Custom ZTag Libraries
#include "DeviceState.h"
#include "EEPROM_Manager.h"
#include "Ble_Manager.h"
#include "Oled_Manager.h"

Ble_Manager bleManager;

void setup() {
    // initialize Serial Monitor
    Serial.begin(115200);

    init_oled();

    write_oled_line(1, "ZTAG DEVICE");
    Serial.println("ZTAG DEVICE");

    bleManager.initBle();
    Serial.println("Ble Initializing");

    // Get the saved state from EEPROM and output it
    deviceState = init_and_read_device_state();
    numberOfInfectionTicks = 0;   // set the infection counter to zero.
    write_oled_and_serial_line(2, DeviceStateToString(deviceState));
}

void loop() {


    bleManager.scanForZtags();
    bleManager.pritnAllZTagsFound();

    // TODO true is only while BLE conversion work is happening
    if (is_message_ztag("temp")) {

    //     DeviceState receivedState = StringToDeviceState(receivedPacket.message);
    //     // Main behaviour loop, only entered if we find a ZTag message
    //     if (DeviceState::human == deviceState) {

    //         if (DeviceState::infected == receivedState) {
    //             is_infected_yet(receivedPacket.rssi);
    //         }

    //         // TODO: Decision time, currently we don't reset the health bar if
    //         // you go in a medical
    //         //  zone whilst a human. Maybe we should. If we should then set to
    //         //  medicalzone here.

    //     } else if (DeviceState::infected == deviceState) {

    //         if (DeviceState::medicalzone == receivedState) {
    //             deviceState = DeviceState::medicalzone;
    //         }

    //     } else if (DeviceState::medicalzone == deviceState) {

    //         Serial.println("Currently in a medical zone");
    //         reset_infection_ticker();
    //         reset_health();
    //         deviceState = DeviceState::human;
    //     }
    // } else {
    //     Serial.println("Packet something else ignoring");
    }

    // Update screen with status (probably don't need to do this every loop)
    // i.e. stick this in a function and call it on any changes?
    Serial.println("[x] Device Stats Start");
    String stateString = "Cur Dev State: ";
    String fullStateString = stateString + DeviceStateToString(deviceState);
    write_oled_and_serial_line(2, fullStateString.c_str());
    String healthStr = "Health: ";
    String fullHealthStr = healthStr + wearableHealth.health;
    write_oled_and_serial_line(4, fullHealthStr.c_str());
    Serial.println("[x] Device Stats Finish");
}
