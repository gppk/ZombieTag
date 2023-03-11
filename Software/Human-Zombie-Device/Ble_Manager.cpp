#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include "Ble_Manager.h"

int scanTime = 5; //In seconds
BLEScan* pBLEScan;

std::vector<ReceivedPacket> foundZtagData;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
        // If we find a zTag device then store that in foundZTagData        
        ReceivedPacket receivedPacket;
        receivedPacket.setMessage(advertisedDevice.getName().c_str());
        receivedPacket.setRssi(advertisedDevice.getRSSI());
        foundZtagData.push_back(receivedPacket);
        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
    }
};

//TODO: Can this return a bool to show it actually worked?
void init_ble() {
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

// Scans for <scanTime> seconds and stores any zTag data in foundZtagData vector
void scan_for_ztags() {
    foundZtagData.clear(); // Reset the found ztags

    BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
    Serial.print("ZTag Devices found: ");
    Serial.println(foundDevices.getCount());
    Serial.println("Scan done!");

    pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory

    // Now we've found a bunch of ZTag obejcts well need to figure out what to do with them.
}

void print_all_ztags_found(){
    Serial.println("Printing ZTags: ");
    for(ReceivedPacket packet : foundZtagData) {
        Serial.println(packet.getMessage());
    }
}


int ReceivedPacket::getRssi() {
    return this->rssi;
}
String ReceivedPacket::getMessage() {
    return this->message;
}
void ReceivedPacket::setRssi(int rssi) {
    this->rssi = rssi;
}
void ReceivedPacket::setMessage(String message) {
    this->message = message;
}