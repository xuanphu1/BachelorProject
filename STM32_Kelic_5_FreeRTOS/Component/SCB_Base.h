#ifndef __SCB_BASE_H__
#define __SCB_BASE_H__
#include "stdint.h"

typedef struct
{
    uint32_t SCB_CPUID;
    uint32_t SCB_ICSR;
    uint32_t SCB_VTOR;
    uint32_t SCB_AIRCR;
    uint32_t SCB_SCR;
    uint32_t SCB_CCR;
    uint32_t SCB_SHPR1;
    uint32_t SCB_SHPR2;
    uint32_t SCB_SHPR3;
    uint32_t SCB_SHCSR;
    // Register remaining
}SCB_Base_t;



#define SCB_BASE_ADDRESS 0xE000ED00UL
#define SCB_BASE_HANDMADE ((volatile SCB_Base_t*)SCB_BASE_ADDRESS)




#define SCB_AIRCR_VECTKEY 0x05FAUL
#define SCB_AIRCR_VECTKEY_POS 16


#define SCB_AIRCR_SYSRESETREQ_POS 2
#define SCB_AIRCR_SYSRESETREQ_MASK 0x00000004UL

#define SCB_AIRCR_PRIGROUP_POS 8
#define SCB_AIRCR_PRIGROUP_MASK 0x00000700UL

#define SCB_ICSR_PENDSTSET_POS 26
#define SCB_ICSR_PENDSTSET_MASK ~(1 << SCB_ICSR_PENDSTSET_POS)

#define SCB_ICSR_PENDSVSET_POS 28
#define SCB_ICSR_PENDSVSET_MASK ~(1 << SCB_ICSR_PENDSTSET_POS)



void NVIC_SystemReset_handmade(void);
void NVIC_SetVectorTable(uint32_t Address_vectorTable);
void TriggerSV_Call_Interrupt(void);
#endif // __SCB_BASE_H__


