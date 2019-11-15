typedef union  {
     uint32_t i;
     uint8_t  packet[4];
} midiPacket_t;

#define stsd (pk.packet[1] & 0xF0) 
#define gatelow userUnits[u]->tGate.gate.lower
#define gatehigh userUnits[u]->tGate.gate.upper

#include <libMMM.h>

void dumpPck(midiPacket_t *pck){
   Serial.print("midiPacket: ");
   Serial.print(pck->packet[1], HEX);if(pck->packet[1] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[2], HEX);if(pck->packet[2] < 0x10){Serial.print("0");}Serial.print(" ");
   Serial.print(pck->packet[3], HEX);if(pck->packet[3] < 0x10){Serial.print("0");}Serial.println(" ");
}

struct userUnit {
    uint8_t cmdCode;
    transformerParms_t tParms; 
    transformerGate_t tGate; 
};

userUnit* userUnits[16];
uint8_t userUnitCount = 0;

void lib3m_AddUserUnit(uint8_t cmdCode, uint8_t x, uint8_t y, uint8_t z, uint8_t g_low, uint8_t g_high)
{
    userUnit* uu = (userUnit*)malloc(sizeof(userUnit)); 
    uu->cmdCode = cmdCode;
    uu->tGate.gate.lower = g_low;
    uu->tGate.gate.upper = g_high;
    uu->tParms.x = x;
    uu->tParms.y = y;
    uu->tParms.z = z;
    userUnits[userUnitCount++] = uu;   
}

void lib3m_ProcessEvent(midiPacket_t &pk)
{            
    for (int u=0;u<userUnitCount;u++){
        if ( BETWEEN(stsd,gatelow,gatehigh) || BETWEEN(pk.packet[1],gatelow,gatehigh) ){      
           (transformerCommands[userUnits[u]->cmdCode].fnFn)(&pk, userUnits[u]->tParms);
        }
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
 
  lib3m_AddUserUnit(evm, stsCONTINUE, stsSTART, 0, stsCONTINUE, stsCONTINUE);
  lib3m_AddUserUnit(gvo, 20         , 0       , 0, stsNOTEOFF , stsNOTEON);

  midiPacket_t pk = { .packet = { 0x0, stsCONTINUE, 0x0, 0x0 } };
  test(pk);
  
  midiPacket_t pk2 = { .packet = { 0x0, stsNOTEON, 0x10, 0x10 } };
  test(pk2);  
}
