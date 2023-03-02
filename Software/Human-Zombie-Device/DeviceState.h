#ifndef DEVICE_STATE_H
#define DEVICE_STATE_H

#include <Arduino.h>
#include <cstring>
#include <stdbool.h>
#include <string.h>

enum DeviceState { initialising, human, infected, medicalzone, null };

const char *DeviceStateToString(enum DeviceState ds);

enum DeviceState StringToDeviceState(String s);

bool is_message_ztag(String recievedLoraMessage);

#endif   // DEVICE_STATE_H
