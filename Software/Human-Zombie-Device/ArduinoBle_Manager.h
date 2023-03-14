#ifndef ARDUINOBLE_MANAGER_H
#define ARDUINOBLE_MANAGER_H


class ArduinoBle_Manager
{
private:

public:
    bool initBleZTagDevice();

    void updateZtagBeaconName(const char* newBeaconName);

    void pollBle();
};

#endif   // ARDUINOBLE_MANAGER_H