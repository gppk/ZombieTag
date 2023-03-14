#ifndef ARDUINOBLE_MANAGER_H
#define ARDUINOBLE_MANAGER_H

// External Arduino LIB.
#include <ArduinoBLE.h>

#include <vector>

// Internal ZTag libs for Device Understanding
#include "ReceivedPacket.h"

class ArduinoBle_Manager
{
private:

    // Had to make this static because it's used in the callback
    // which has to be static because otherwise I couldn't get setEventHandler to compile with it
    // There may be a better way, if there is i'd love to know it.
    static std::vector<ReceivedPacket> foundZtagDevices;

    // Internal Callback function that gets called everytime a new device is found
    // whilst poll is running
    static void bleCentralDiscoverHandler(BLEDevice peripheral);


public:

    /**
     * Begins the BLE Object, and sets up all default init work
     * Should have BLE running and advertising itself after this function 
     * 
     * @return bool - whether or not the init succeeded
     */
    bool initBleZTagDevice();

    /**
     * Performs all commands needed to update the beacons name
     * and ensure that it is re-advertising with that name 
     */
    void updateZtagBeaconName(const char* newBeaconName);

    /**
     * Very simple function that wraps the BLE.poll command
     */
    void pollBle();

    /**
     * Give access via the API to the most recently collected set of ZTag Devices
     * 
     * These devices will have been found using a Ble Poll via the bleCentralDiscoverHandler callback.
     * It will store all found devices since the last time that pollBle() is called. It gets reset when
     * that is called.
     * 
     * Why is this ZTag devices and not all devices? - Because I'm concerned that in a high-pop
     * area we could fill up the ESP memory very quickly, so I'm going to dump any devices we see 
     * that aren't ztag devices in the callback and only store ZTag. This brings some ZTag specific
     * into this BLE manager but quite frankly, that's for the best in this case. 
     * And I think, unavoidable.
     * 
     * No setter required, variable directly accessible from within ArduinoBle_Manager and should only be set there
     * 
     * @return foundZtagDevices, a collection of recieved objects
     */
    std::vector<ReceivedPacket> getFoundZtagDevices();
    
};

#endif   // ARDUINOBLE_MANAGER_H