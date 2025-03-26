#ifndef _FREE_RTOS_HANDMADE_
#define _FREE_RTOS_HANDMADE_
#include "stdint.h"
#include "cortex_m3.h"

typedef struct 
{
   CPU_TypeDef CPU;
   unsigned long Stackp[256]; // 1KB

    
}Task_TypeDef_t;

extern Task_TypeDef_t Task[2];

#endif