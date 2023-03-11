#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

class Ble_Manager
{
private:
    /* data */
    void processZtags();
public:
    void initBle();
    void scanForZtags();
    void pritnAllZTagsFound();
};

#endif   // BLE_MANAGER_H