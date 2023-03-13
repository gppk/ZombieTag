#include "ArduinoBle_Manager.h"

// External Arduino LIB.
#include <ArduinoBLE.h>

// Internal Callback function
void bleCentralDiscoverHandler(BLEDevice peripheral);

bool ArduinoBle_Manager::initBleZTagDevice() {

    bool ret = BLE.begin();
    BLE.setDeviceName("ZTag");
    BLE.setLocalName("ZTag");
    BLE.advertise();

    BLE.setEventHandler(BLEDiscovered, bleCentralDiscoverHandler);
    BLE.scan(true);

    return ret;
}

void ArduinoBle_Manager::updateZtagBeaconName(String newBeaconName) {

    BLE.setDeviceName(newBeaconName.c_str());
    BLE.setLocalName(newBeaconName.c_str());
    BLE.advertise();
}

void ArduinoBle_Manager::pollBle(){
    BLE.poll(100);
}

void bleCentralDiscoverHandler(BLEDevice peripheral) {
  // discovered a peripheral
  Serial.println("Discovered a peripheral");
  Serial.println("-----------------------");

  // print address
  Serial.print("Address: ");
  Serial.println(peripheral.address());

  // print the local name, if present
  if (peripheral.hasLocalName()) {
    Serial.print("Local Name: ");
    Serial.println(peripheral.localName());
  }

  // print the advertised service UUIDs, if present
  if (peripheral.hasAdvertisedServiceUuid()) {
    Serial.print("Service UUIDs: ");
    for (int i = 0; i < peripheral.advertisedServiceUuidCount(); i++) {
      Serial.print(peripheral.advertisedServiceUuid(i));
      Serial.print(" ");
    }
    Serial.println();
  }

  // print the RSSI
  Serial.print("RSSI: ");
  Serial.println(peripheral.rssi());

  Serial.println();
}
