typedef union  {
     uint32_t i;
     uint8_t  packet[4];
} midiPacket_t;

#include <libMMM.h>

void dumpPck(midiPacket_t *pck){
   Serial.print("midiPacket: ");
   Serial.print(pck->packet[1], HEX);if(pck->packet[1] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[2], HEX);if(pck->packet[2] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[3], HEX);if(pck->packet[3] < 0x10){Serial.print("0");}Serial.println(" ");
}

struct userUnit {
    uint8_t mUnitIdx;
    transformerParms_t tParms; 
};

userUnit* userUnits[16];
uint8_t userUnitCount = 0;

void lib3m_AddUserUnit(uint8_t mUnitIdx, uint8_t x, uint8_t y, uint8_t z)
{
    userUnit* uu = (userUnit*)malloc(sizeof(userUnit)); 
    uu->mUnitIdx = mUnitIdx;
    uu->tParms.x = x;
    uu->tParms.y = y;
    uu->tParms.z = z;
    userUnits[userUnitCount++] = uu;   
}

void lib3m_ProcessEvent(midiPacket_t &pck)
{            
    for (int u=0;u<userUnitCount;u++){
        if (!userUnits[u]->tParms.z||stsd==userUnits[u]->tParms.z)(transformerCommands[userUnits[u]->mUnitIdx].fnFn)(&pck, userUnits[u]->tParms);
    }
} 

void test(midiPacket_t pk){
  dumpPck(&pk);
  lib3m_ProcessEvent(pk);
  dumpPck(&pk);
}

void setup(){

  Serial.begin(9600);
  delay(3000);
  
  lib3m_AddUserUnit(evm, stsCONTINUE, stsSTART, 0);
  lib3m_AddUserUnit(gvo, 20, 0, 9);

  midiPacket_t pk = { .packet = { 0x0, stsCONTINUE, 0x0, 0x0 } };
  test(pk);
  
  midiPacket_t pk2 = { .packet = { 0x0, stsNOTEON, 0x10, 0x10 } };
  test(pk2);  
}
