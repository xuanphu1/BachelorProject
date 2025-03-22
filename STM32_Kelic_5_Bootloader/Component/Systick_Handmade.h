#ifndef SYSTICK_HANDMADE_H
#define SYSTICK_HANDMADE_H
#include "stdint.h" // Giả định Std_Type.h định nghĩa các kiểu dữ liệu cơ bản như uint32_t
#include "RCC_Handmade.h"


// Cấu trúc mô tả khối thanh ghi SysTick
typedef struct {
    volatile uint32_t SYST_CSR;    // 0xE000E010 - Control and Status Register (RW)
    volatile uint32_t SYST_RVR;    // 0xE000E014 - Reload Value Register (RW)
    volatile uint32_t SYST_CVR;    // 0xE000E018 - Current Value Register (RW)
    volatile uint32_t SYST_CALIB;  // 0xE000E01C - Calibration Value Register (RO)
} SysTick_Handmade_t;

// Địa chỉ base của SysTick trong Cortex-M
#define SYSTICK_BASE_ADDRESS    0xE000E010UL
#define SYSTICK_HANDMADE                 ((volatile SysTick_Handmade_t*) (SYSTICK_BASE_ADDRESS))

#define TENMS_SYSTICK_1MS 9000 

typedef enum {
    SYST_CSR_ENABLE_DISABLE = 0,  // Counter disabled
    SYST_CSR_ENABLE_ENABLE  = 1   // Counter enabled
} SysTick_CSR_Enable_t;

#define CHECK_FLAG_COUNTER ((SYSTICK_HANDMADE->SYST_CSR >> 16) & (0x1))

// TICKINT (bit 1)
typedef enum {
    SYST_CSR_TICKINT_DISABLE = 0,  // Count to 0 does not generate interrupt
    SYST_CSR_TICKINT_ENABLE  = 1   // Count to 0 generates interrupt
} SysTick_CSR_TickInt_t;

// CLKSOURCE (bit 2)
typedef enum {
    SYST_CSR_CLKSOURCE_EXTERNAL = 0,  // External reference clock
    SYST_CSR_CLKSOURCE_PROCESSOR = 1  // Processor clock
} SysTick_CSR_ClockSource_t;

// COUNTFLAG (bit 16, read-only)
typedef enum {
    SYST_CSR_COUNTFLAG_NO  = 0,  // Timer has not counted to 0
    SYST_CSR_COUNTFLAG_YES = 1   // Timer has counted to 0
} SysTick_CSR_CountFlag_t;


typedef struct  
{
    SysTick_CSR_ClockSource_t SysTick_Source;
    SysTick_CSR_TickInt_t Generate_interrupt;
    SysTick_CSR_CountFlag_t EnableCounter;
    uint32_t ValueInitReload;
}SysTick_Config_t;


// Hàm khởi tạo SysTick (ví dụ)
void SysTick_Init(SysTick_Config_t *systickConfig);
void Delay_SysTick(uint32_t value_ms);

#endif // SYSTICK_HANDMADE_H

