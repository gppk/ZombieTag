#ifndef ReceivedPacket_H
#define ReceivedPacket_H

#include <Arduino.h>

// Data structure for storing found data
class ReceivedPacket
{
private:
    int rssi;
    String message;
public:
    
    int getRssi();
    String getMessage();

    void setRssi(int rssi);
    void setMessage(String message);
};
#endif //ReceivedPacket_H