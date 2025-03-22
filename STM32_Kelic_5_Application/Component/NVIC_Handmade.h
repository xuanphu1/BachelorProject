#ifndef NVIC_HANDMADE_H
#define NVIC_HANDMADE_H
#include "RCC_Handmade.h"
#include "stdint.h"
// Giả định cấu trúc EXTI_Handmade_t
typedef struct {
    volatile uint32_t ICTR;       // 0xE000E004 - Interrupt Controller Type Register (RO)
    uint32_t RESERVED0[62];        // Padding để căn chỉnh đến 0xE000E100

    volatile uint32_t ISER[8];    // 0xE000E100 - Interrupt Set-Enable Registers (RW)
    uint32_t RESERVED1[24];       // Padding để căn chỉnh đến 0xE000E180

    volatile uint32_t ICER[8];    // 0xE000E180 - Interrupt Clear-Enable Registers (RW)
    uint32_t RESERVED2[24];       // Padding để căn chỉnh đến 0xE000E200

    volatile uint32_t ISPR[8];    // 0xE000E200 - Interrupt Set-Pending Registers (RW)
    uint32_t RESERVED3[24];       // Padding để căn chỉnh đến 0xE000E280

    volatile uint32_t ICPR[8];    // 0xE000E280 - Interrupt Clear-Pending Registers (RW)
    uint32_t RESERVED4[24];       // Padding để căn chỉnh đến 0xE000E300

    volatile uint32_t IABR[8];    // 0xE000E300 - Interrupt Active Bit Registers (RO)
    uint32_t RESERVED5[56];       // Padding để căn chỉnh đến 0xE000E400

    volatile uint32_t IPR[60];    // 0xE000E400 - Interrupt Priority Registers (RW)
} NVIC_Handmade_t;

// Địa chỉ base của NVIC trong STM32F103 (Cortex-M3)
#define NVIC_BASE_ADDRESS   0xE000E004UL
#define NVIC_HANDMADE       ((volatile NVIC_Handmade_t*) (NVIC_BASE_ADDRESS))

typedef enum {
    Custom_WWDG_IRQn = 0,             // Window Watchdog interrupt
    Custom_PVD_IRQn = 1,              // PVD through EXTI Line detection interrupt
    Custom_TAMPER_IRQn = 2,           // Tamper interrupt
    Custom_RTC_IRQn = 3,              // RTC global interrupt
    Custom_FLASH_IRQn = 4,            // Flash global interrupt
    Custom_RCC_IRQn = 5,              // RCC global interrupt
    Custom_EXTI0_IRQn = 6,            // EXTI Line0 interrupt
    Custom_EXTI1_IRQn = 7,            // EXTI Line1 interrupt
    Custom_EXTI2_IRQn = 8,            // EXTI Line2 interrupt
    Custom_EXTI3_IRQn = 9,            // EXTI Line3 interrupt
    Custom_EXTI4_IRQn = 10,           // EXTI Line4 interrupt
    Custom_DMA1_Channel1_IRQn = 11,   // DMA1 Channel1 global interrupt
    Custom_DMA1_Channel2_IRQn = 12,   // DMA1 Channel2 global interrupt
    Custom_DMA1_Channel3_IRQn = 13,   // DMA1 Channel3 global interrupt
    Custom_DMA1_Channel4_IRQn = 14,   // DMA1 Channel4 global interrupt
    Custom_DMA1_Channel5_IRQn = 15,   // DMA1 Channel5 global interrupt
    Custom_DMA1_Channel6_IRQn = 16,   // DMA1 Channel6 global interrupt
    Custom_DMA1_Channel7_IRQn = 17,   // DMA1 Channel7 global interrupt
    Custom_ADC1_2_IRQn = 18,          // ADC1 and ADC2 global interrupt
    Custom_USB_HP_CAN_TX_IRQn = 19,   // USB High Priority or CAN TX interrupts
    Custom_USB_LP_CAN_RX0_IRQn = 20,  // USB Low Priority or CAN RX0 interrupts
    Custom_CAN_RX1_IRQn = 21,         // CAN RX1 interrupt
    Custom_CAN_SCE_IRQn = 22,         // CAN SCE interrupt
    Custom_EXTI9_5_IRQn = 23,         // EXTI Line[9:5] interrupts
    Custom_TIM1_BRK_IRQn = 24,        // TIM1 Break interrupt
    Custom_TIM1_UP_IRQn = 25,         // TIM1 Update interrupt
    Custom_TIM1_TRG_COM_IRQn = 26,    // TIM1 Trigger and Commutation interrupts
    Custom_TIM1_CC_IRQn = 27,         // TIM1 Capture Compare interrupt
    Custom_TIM2_IRQn = 28,            // TIM2 global interrupt
    Custom_TIM3_IRQn = 29,            // TIM3 global interrupt
    Custom_TIM4_IRQn = 30,            // TIM4 global interrupt
    Custom_I2C1_EV_IRQn = 31,         // I2C1 event interrupt
    Custom_I2C1_ER_IRQn = 32,         // I2C1 error interrupt
    Custom_I2C2_EV_IRQn = 33,         // I2C2 event interrupt
    Custom_I2C2_ER_IRQn = 34,         // I2C2 error interrupt
    Custom_SPI1_IRQn = 35,            // SPI1 global interrupt
    Custom_SPI2_IRQn = 36,            // SPI2 global interrupt
    Custom_USART1_IRQn = 37,          // USART1 global interrupt
    Custom_USART2_IRQn = 38,          // USART2 global interrupt
    Custom_USART3_IRQn = 39,          // USART3 global interrupt
    Custom_EXTI15_10_IRQn = 40,       // EXTI Line[15:10] interrupts
    Custom_RTCAlarm_IRQn = 41,        // RTC alarm through EXTI line interrupt
    Custom_USBWakeup_IRQn = 42,       // USB wakeup from suspend through EXTI line interrupt
    Custom_TIM8_BRK_IRQn = 43,        // TIM8 Break interrupt
    Custom_TIM8_UP_IRQn = 44,         // TIM8 Update interrupt
    Custom_TIM8_TRG_COM_IRQn = 45,    // TIM8 Trigger and Commutation interrupts
    Custom_TIM8_CC_IRQn = 46,         // TIM8 Capture Compare interrupt
    Custom_ADC3_IRQn = 47,            // ADC3 global interrupt
    Custom_FSMC_IRQn = 48,            // FSMC global interrupt
    Custom_SDIO_IRQn = 49,            // SDIO global interrupt
    Custom_TIM5_IRQn = 50,            // TIM5 global interrupt
    Custom_SPI3_IRQn = 51,            // SPI3 global interrupt
    Custom_UART4_IRQn = 52,           // UART4 global interrupt
    Custom_UART5_IRQn = 53,           // UART5 global interrupt
    Custom_TIM6_IRQn = 54,            // TIM6 global interrupt
    Custom_TIM7_IRQn = 55,            // TIM7 global interrupt
    Custom_DMA2_Channel1_IRQn = 56,   // DMA2 Channel1 global interrupt
    Custom_DMA2_Channel2_IRQn = 57,   // DMA2 Channel2 global interrupt
    Custom_DMA2_Channel3_IRQn = 58,   // DMA2 Channel3 global interrupt
    Custom_DMA2_Channel4_5_IRQn = 59  // DMA2 Channel4 and Channel5 global interrupts
} Custom_IRQn;

#define SET_PRI(x, y) ((x) << (4 + (y) * 8))

void Enable_Intterupt_NVIC(Custom_IRQn IRQ);
void Disable_Intterupt_NVIC(Custom_IRQn IRQ);
void setPriorityInterrupt(Custom_IRQn IRQ, uint8_t Priority);


#endif // NVIC_HANDMADE_H

