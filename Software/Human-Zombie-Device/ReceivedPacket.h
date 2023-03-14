#ifndef ReceivedPacket_H
#define ReceivedPacket_H

#include <Arduino.h>

// Data structure for storing found data
class ReceivedPacket
{
private:
    int rssi;
    String deviceName;
public:
    
    int getRssi();
    String getDeviceName();

    void setRssi(int rssi);
    void setDeviceName(String deviceName);
};
#endif //ReceivedPacket_H