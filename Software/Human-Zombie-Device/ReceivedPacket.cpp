#include "ReceivedPacket.h"

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