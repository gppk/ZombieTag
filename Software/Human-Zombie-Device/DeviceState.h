#ifndef DEVICE_STATE_H
#define DEVICE_STATE_H

enum DeviceState {
    initialising,
    human,
    infected,
    medicalzone,
    null
};

const char* DeviceStateToString( DeviceState ds ); 

DeviceState StringToDeviceState (String s);

bool is_message_ztag ( String recievedLoraMessage );

#endif //DEVICE_STATE_H
