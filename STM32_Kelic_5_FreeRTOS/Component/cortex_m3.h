#ifndef _CORTEX_M3_H_
#define _CORTEX_M3_H_

//==============================================================================================================================================================
//==================================================                   CPU Registers            ================================================================
//==============================================================================================================================================================
typedef struct
{ //0xFFFF'FFFF9
  unsigned int R0;
  unsigned int R1;
  unsigned int R2;
  unsigned int R3;
  unsigned int R12;
  unsigned int LR;
  unsigned int PC;
  unsigned int EAPSR;
  
  unsigned int R4;
  unsigned int R5;
  unsigned int R6;
  unsigned int R7;
  unsigned int R8;
  unsigned int R9;
  unsigned int R10;
  unsigned int R11;
  unsigned int SP;
} CPU_TypeDef;



//void DisableAllInterrupt(void);

//void EnableAllInterrupt(void);
#endif


