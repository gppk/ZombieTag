#include "ReceivedPacket.h"

int ReceivedPacket::getRssi() {
    return this->rssi;
}
String ReceivedPacket::getDeviceName() {
    return this->deviceName;
}
void ReceivedPacket::setRssi(int rssi) {
    this->rssi = rssi;
}
void ReceivedPacket::setDeviceName(String deviceName) {
    if (deviceName.isEmpty()){
        deviceName = "ZTag-ERROR";
    }
    
    this->deviceName = deviceName;
}