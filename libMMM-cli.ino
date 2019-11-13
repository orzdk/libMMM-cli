#include <libMMM.h>

void dumpPck(midiPacket *pck){
   Serial.print("midiPacket: ");
   Serial.print(pck->packet[1], HEX);if(pck->packet[1] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[2], HEX);if(pck->packet[2] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[3], HEX);if(pck->packet[3] < 0x10){Serial.print("0");}Serial.println(" ");
}

void test(midiPacket pk){
  dumpPck(&pk);
  lib3m_ProcessEvent(pk);
  dumpPck(&pk);
}

void setup(){

  Serial.begin(9600);
  delay(3000);
  
  lib3m_AddUserUnit(evm, stsCONTINUE, stsSTART, 0);
  lib3m_AddUserUnit(gvo, 20, 0, 9);

  midiPacket pk = { .packet = { 0x0, stsCONTINUE, 0x0, 0x0 } };
  test(pk);
  
  midiPacket pk2 = { .packet = { 0x0, stsNOTEON, 0x10, 0x10 } };
  test(pk2);  
}
