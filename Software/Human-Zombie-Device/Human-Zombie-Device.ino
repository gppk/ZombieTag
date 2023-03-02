// add in this
// https://hackmd.io/@exradr/clang-format

// code for DOITESP32 DEVKIT V1

// Custom ZTag Libraries
#include "DeviceState.h"
#include "EEPROM_Manager.h"
#include "Lora_Manager.h"
#include "Oled_Manager.h"

// deviceState set from EEPROM in setup
DeviceState deviceState;

void
setup() {
    // initialize Serial Monitor
    Serial.begin(115200);

    init_oled();

    write_oled_line(1, "ZTAG DEVICE");
    Serial.println("ZTAG DEVICE");

    if (!init_lora()) {
        Serial.println("Starting LoRa failed!");
        write_oled_and_serial_line(3, "!!LORA FAILED!!");
        while (1)
            ;
    }
    Serial.println("LoRa Initializing OK!");

    // Get the saved state from EEPROM and output it
    deviceState = init_and_read_device_state();
    write_oled_and_serial_line(2, DeviceStateToString(deviceState));
}

void
loop() {

    if (is_message_ztag(get_new_lora_packet())) {

        Serial.println("ZTAg Packet received, doing switch now");
        DeviceState receivedState = StringToDeviceState(receivedPacket.message);
        // Main behaviour loop
        if (DeviceState::human == deviceState) {
            Serial.println("Currently Human, investigating new packet");
            if (DeviceState::infected == receivedState) {
                deviceState = DeviceState::infected;
                Serial.println("INFECTED!!! Going to infected state");
                write_oled_and_serial_line(2, DeviceStateToString(deviceState));
            }
            Serial.println("Done in Human state checking");
        } else if (DeviceState::infected == deviceState) {
            Serial.println("Currently infected, investigating new packet");
            if (DeviceState::medicalzone == receivedState) {
                deviceState = DeviceState::human;
                Serial.println("Got to SAFETY!!! Going to human state");
                write_oled_and_serial_line(2, DeviceStateToString(deviceState));
            }
            Serial.println("Done in infected state checking");

        } else if (DeviceState::medicalzone == deviceState) {
            Serial.println(
                "Currently in a medical zone, investigating new packet");
            Serial.println("Done in medicalzone");
        } else {
            display.setCursor(0, 10);
            display.println("BROKE");
            display.display();
            Serial.print("Current deviceState: ");
            Serial.println(deviceState);
            Serial.println("Hit a fail mode, no recovery. Restart");
        }

    } else {
        Serial.println("Packet something else ignoring");
    }
}
