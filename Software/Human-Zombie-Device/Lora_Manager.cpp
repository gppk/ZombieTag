#include <Arduino.h>

//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>
#include "Lora_Manager.h"

ReceivedPacket receivedPacket;

bool init_lora() {
    bool ret = false;
    //SPI LoRa pins
    SPI.begin(SCK, MISO, MOSI, SS);
    //setup LoRa transceiver module
    LoRa.setPins(SS, RST, DIO0);

    if (LoRa.begin(BAND)) {
        ret = true;
    }
    return ret;
}

// Also stores into the recievedPacket storage object for later retrieval
// but returns string so we can get an instantaneous response for the packet
// rather than trusting the storage
String get_new_lora_packet() {
    // Get a packet - needs its own function
    bool packetFound = false;
    String loraData;

    while( !packetFound ) {
        //try to parse packet
        int packetSize = LoRa.parsePacket();
        if ( packetSize ) {
            //received a packet
            Serial.println("###############");
            Serial.print("Received packet: ");

            //read packet
            while (LoRa.available()) {
                loraData = LoRa.readString();
                Serial.println(loraData);
            }

            receivedPacket.rssi = LoRa.packetRssi();
            receivedPacket.message = loraData;
            Serial.println("Data in RSSI Packet");
            Serial.print("Message: ");
            Serial.println(receivedPacket.message);
            Serial.print("RSSI: ");
            Serial.println(receivedPacket.rssi);
            Serial.println("###############");
            packetFound = true;
        }
    }
    return receivedPacket.message;
}