#include "cortex_m3.h"


//void DisableAllInterrupt(void)
//{
//    __asm("cpsid i" : : : "memory");
//}

//void EnableAllInterrupt(void)
//{
//    __asm("cpsie i" : : : "memory");
//}


//void TaskENTER_CRITICAL(void){
//    unsigned short priority_mask = 2 << 4; // Ch?n t?t c? interrupt có priority >= 2
//    __asm volatile("msr BASEPRI, %0" :: "r" (priority_mask) : "memory");
//}

//void TaskEXIT_CRITICAL(void){
//    __asm volatile("msr BASEPRI, %0" :: "r" (0) : "memory"); // M? l?i toàn b? interrupt
//}


void TaskENTER_CRITICAL(void){
    //__set_BASEPRI(0x20); // 0x20 = priority 2 << 4
		__disable_irq();
}

void TaskEXIT_CRITICAL(void){
    //__set_BASEPRI(0);    // M? l?i toàn b? interrupt
		__enable_irq();
}

