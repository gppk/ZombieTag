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

void get_new_lora_packet() {
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
            
            // Needs finishing
            if ( loraData == "infected" ) { // or any of the other known strings
                Serial.println("Found a ZTag Identifier");
                packetFound = true;
            }
            else {
                Serial.println("No ZTag Identifier Found");
            }
            Serial.println("###############");
        }
    }
}