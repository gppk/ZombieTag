#include "ArduinoBle_Manager.h"

// Internal ZTag libs for Device Understanding
#include "DeviceState.h"

#include "SerialHelper.h"

#define BLE_POLL_TIMEOUT_MS (1000) 
#define BLE_DEFAULT_NAME    ("ZTag")

std::vector<ReceivedPacket> ArduinoBle_Manager::foundZtagDevices;

bool ArduinoBle_Manager::initBleZTagDevice() {

    bool ret = BLE.begin();
    BLE.setDeviceName(BLE_DEFAULT_NAME);
    BLE.setLocalName(BLE_DEFAULT_NAME);
    BLE.advertise();

    BLE.setEventHandler(BLEDiscovered, bleCentralDiscoverHandler);
    BLE.scan(true); //not sure why this overrides the default of false, but comes from demo code

    return ret;
}

void ArduinoBle_Manager::updateZtagBeaconName(const char* newBeaconName) {
    BLE.setDeviceName(newBeaconName);
    BLE.setLocalName(newBeaconName);
    BLE.advertise();
}

void ArduinoBle_Manager::pollBle(){
    // We're doing a new scan, so clear old scan results
    foundZtagDevices.clear(); 
    BLE.poll(BLE_POLL_TIMEOUT_MS);
}

void ArduinoBle_Manager::bleCentralDiscoverHandler(BLEDevice peripheral) {
  
  bool isZtagDevice = false;
  // The first thing we need to do is figure out if it's a ZTag device
  // See getFoundZtagDevices() function comment as to why.

  // All ZTags will have local names so we can drop anything that doesn't
  if (peripheral.hasLocalName() && is_message_ztag(peripheral.localName())) {
    isZtagDevice = true;
  }

  // Now we know we have a ZTag device then store it in foundZtagDevices
  if (isZtagDevice)
  {
    // If we find a zTag device then store that in foundZTagData        
    ReceivedPacket receivedPacket;
    receivedPacket.setDeviceName(peripheral.localName());
    receivedPacket.setRssi(peripheral.rssi());
    foundZtagDevices.push_back(receivedPacket);
  }
}

std::vector<ReceivedPacket> ArduinoBle_Manager::getFoundZtagDevices() {
  return foundZtagDevices;
}
