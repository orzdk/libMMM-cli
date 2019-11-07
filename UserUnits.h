
  void mmm_SetupUserData(){
    
    addUserUnit("---> Replace Continue w. Start" , FN_ANY_REPLACE     , 0x000001FA ); //Set Byte to FA
    addUserUnit("---> Add 10 to Velocity"        , FN_ANY_MODIFY      , 0x0001030A ); //Add 10 to Byte 3
    addUserUnit("---> Max Velocity"              , FN_ANY_REPLACE     , 0x0000037F ); //Set byte 3 to 127
    addUserUnit("---> Change Channel to 11"      , FN_CHANNEL_MODIFY  , 0x0000000B ); //Change nypple 1 of Byte1 to 11
    
    addUserRule("-> Flow Control", stsCONTINUE   , 1, { 0x00, NULL, NULL, NULL }   ); //Unit0 - Replace Continue
    addUserRule("-> Velocity Control", stsNOTEON , 2, { 0x01, 0x03, NULL, NULL }   ); //Unit1+3 - Vel/Channel
    
  }
