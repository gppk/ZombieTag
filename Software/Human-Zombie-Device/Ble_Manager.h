#ifndef BLE_MANAGER_H
#define BLE_MANAGER_H

void init_ble();
void scan_for_ztags();
void print_all_ztags_found();


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



#endif   // BLE_MANAGER_H