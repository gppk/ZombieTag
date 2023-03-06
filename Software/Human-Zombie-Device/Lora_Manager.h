#ifndef LORA_MANAGER_H
#define LORA_MANAGER_H

//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 866E6

struct ReceivedPacket { 
  int rssi;           
  String message;
};

bool init_lora();

extern ReceivedPacket receivedPacket;

// Also stores into the receivedPacket storage object for later retrieval
// but returns string so we can get an instantaneous response for the packet
// rather than trusting the storage
String get_new_lora_packet() ;

#endif //LORA_MANAGER_H