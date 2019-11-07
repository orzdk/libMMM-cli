#include <libMMM.h>
#include "UserUnits.h"
#include "SerialDebug.h"

void setup(){

  Serial.begin(9600);
  delay(3000);
  
  mmm_InitUnits();       //UnitFunctions.h in libMMM arduino library folder
  mmm_SetupUserData();   //UserUnits.h in sketch folder
  
  midiPacket pk = { .packet = { 0x0, stsCONTINUE, 0x0, 0x0 } };
  dumpPck(&pk);
  mmm_ProcessEvent(pk);
  dumpPck(&pk);
  
  Serial.println("-------------------------");
  
  midiPacket pk2 = { .packet = { 0x0, stsNOTEON, 0x50, 0x50 } };
  dumpPck(&pk2);
  mmm_ProcessEvent(pk2);
  dumpPck(&pk2);
  
}
