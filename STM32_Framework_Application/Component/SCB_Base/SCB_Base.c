#include "SCB_Base.h"




void NVIC_SystemReset(void){

    SCB_BASE_HANDMADE->SCB_AIRCR =  (uint32_t)  ((SCB_AIRCR_VECTKEY << SCB_AIRCR_VECTKEY_POS)              | 
                                                (1 << SCB_AIRCR_SYSRESETREQ_POS)                           |
                                                (SCB_BASE_HANDMADE->SCB_AIRCR & SCB_AIRCR_PRIGROUP_MASK))  ;      
                                   
}

void NVIC_SetVectorTable(uint32_t Address_vectorTable){
    SCB_BASE_HANDMADE->SCB_VTOR = Address_vectorTable;
}