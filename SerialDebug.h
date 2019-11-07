#pragma once 

void dumpPck(midiPacket *pck){
   Serial.print("midiPacket: ");
   Serial.print(pck->packet[1], HEX);if(pck->packet[1] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[2], HEX);if(pck->packet[2] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[3], HEX);if(pck->packet[3] < 0x10){Serial.print("0");}Serial.println(" ");
}
