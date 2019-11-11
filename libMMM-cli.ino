#include <libMMM.h>

void DumpPck(midiPacket *pck){
   Serial.print("midiPacket: ");
   Serial.print(pck->packet[1], HEX);if(pck->packet[1] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[2], HEX);if(pck->packet[2] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[3], HEX);if(pck->packet[3] < 0x10){Serial.print("0");}Serial.println(" ");
}

void DumpProcessTest(midiPacket pk){
  DumpPck(&pk);
  lib3m_ProcessEvent(pk);
  DumpPck(&pk);
}
void setup(){

  Serial.begin(9600);
  delay(3000);
  
  lib3m_InitModules();

  lib3m_AddModuleUnit("voup",eventIncByteDef, 3, 0x10, 0, 0);
//  lib3m_AddModuleUnit("vodn",eventDecByteDef, 3, 20, 0, 0);
//  lib3m_AddModuleUnit("ntup",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("ntdn",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("vset",eventSetByteDef, 3, 127, 0, 0);
//  lib3m_AddModuleUnit("cset",eventSetChannelDef, 11, 0, 0, 0);
//
//  lib3m_AddModuleUnit("ctup",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("ctdn",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("cvup",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("cvdn",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("chmp",0, 0, 0, 0, 0);
//  
//  lib3m_AddModuleUnit("ccmp",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("pcmp",0, 0, 0, 0, 0);
  lib3m_AddModuleUnit("evmp",eventSetByteIfDef, 1, stsSTART, 1, stsCONTINUE);
//
//  lib3m_AddModuleUnit("chfl",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("ccfl",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("pcfl",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("evfl",0, 0, 0, 0, 0); 
//
//  lib3m_AddModuleUnit("ntsu",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("ntsl",0, 0, 0, 0, 0); 
//
//  lib3m_AddModuleUnit("gent",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("gecc",0, 0, 0, 0, 0);
//  lib3m_AddModuleUnit("gepc",0, 0, 0, 0, 0);

  
  midiPacket pk = { .packet = { 0x0, stsCONTINUE, 0x0, 0x0 } };
  DumpProcessTest(pk);
  
  midiPacket pk2 = { .packet = { 0x0, stsNOTEON, 0x10, 0x10 } };
  DumpProcessTest(pk2);
  
}
