#ifndef GCC_HANDMADE_H
#define GCC_HANDMADE_H
#include "stdio.h"
#include "stdint.h"
#include "Flash_Handmade.h"

typedef struct {
	
	uint32_t RCC_CR ;
	uint32_t RCC_CFGR ;
	uint32_t RCC_CIR ;
	uint32_t RCC_APB2RSTR ;
	uint32_t RCC_APB1RSTR ;
	uint32_t RCC_AHBENR ;
	uint32_t RCC_APB2ENR ;
	uint32_t RCC_APB1ENR ;
	uint32_t RCC_BDCR ;
	uint32_t RCC_CSR ;
	

}RCC_Handmade_t ;

typedef enum {
    AFIO_EN_CLK       = 0,  // Alternate Function I/O clock enable
    Reserved_0        = 1,  // (Kh�ng s? d?ng)
    IOPA_EN_CLK       = 2,  // GPIOA clock enable
    IOPB_EN_CLK       = 3,  // GPIOB clock enable
    IOPC_EN_CLK       = 4,  // GPIOC clock enable
    IOPD_EN_CLK       = 5,  // GPIOD clock enable
    IOPE_EN_CLK       = 6,  // GPIOE clock enable
    IOPF_EN_CLK       = 7,  // GPIOF clock enable
    IOPG_EN_CLK       = 8,  // GPIOG clock enable
    ADC1_EN_CLK       = 9,  // ADC1 clock enable
    ADC2_EN_CLK       = 10, // ADC2 clock enable
    TIM1_EN_CLK       = 11, // TIM1 clock enable
    SPI1_EN_CLK       = 12, // SPI1 clock enable
    TIM8_EN_CLK       = 13, // TIM8 clock enable
    USART1_EN_CLK     = 14, // USART1 clock enable
    ADC3_EN_CLK       = 15, // ADC3 clock enable
    TIM9_EN_CLK       = 19, // TIM9 clock enable
    TIM10_EN_CLK      = 20, // TIM10 clock enable
    TIM11_EN_CLK      = 21  // TIM11 clock enable
} APB2_Peripheral_Clock;


typedef enum {
    TIM2_EN_CLK       = 0,  // TIM2 clock enable
    TIM3_EN_CLK       = 1,  // TIM3 clock enable
    TIM4_EN_CLK       = 2,  // TIM4 clock enable
    TIM5_EN_CLK       = 3,  // TIM5 clock enable
    TIM6_EN_CLK       = 4,  // TIM6 clock enable
    TIM7_EN_CLK       = 5,  // TIM7 clock enable
    TIM12_EN_CLK      = 6,  // TIM12 clock enable
    TIM13_EN_CLK      = 7,  // TIM13 clock enable
    TIM14_EN_CLK      = 8,  // TIM14 clock enable
    WWDG_EN_CLK       = 11, // Window Watchdog clock enable
    SPI2_EN_CLK       = 14, // SPI2 clock enable
    SPI3_EN_CLK       = 15, // SPI3 clock enable
    USART2_EN_CLK     = 17, // USART2 clock enable
    USART3_EN_CLK     = 18, // USART3 clock enable
    UART4_EN_CLK      = 19, // UART4 clock enable
    UART5_EN_CLK      = 20, // UART5 clock enable
    I2C1_EN_CLK       = 21, // I2C1 clock enable
    I2C2_EN_CLK       = 22, // I2C2 clock enable
    USB_EN_CLK        = 23, // USB clock enable
    CAN1_EN_CLK       = 25, // CAN1 clock enable
    BKP_EN_CLK        = 27, // Backup interface clock enable
    PWR_EN_CLK        = 28, // Power interface clock enable
    DAC_EN_CLK        = 29  // DAC clock enable
} APB1_Peripheral_Clock;


typedef enum {
    DMA1_EN_CLK       = 0,  // DMA1 clock enable
    DMA2_EN_CLK       = 1,  // DMA2 clock enable
    SRAM_EN_CLK       = 2,  // SRAM clock enable
    FLITF_EN_CLK      = 4,  // FLITF clock enable (Flash interface)
    CRC_EN_CLK        = 6,  // CRC clock enable
    FSMC_EN_CLK       = 8,  // FSMC clock enable
    SDIO_EN_CLK       = 10  // SDIO clock enable
} AHB_Peripheral_Clock;

typedef enum {
    HSI_CLOCK = 0, // High-speed internal clock
    HSE_CLOCK = 1, // High-speed external clock
}Source_Clock_t;

enum {
    DISABLE_RCC = 0,
    ENABLE_RCC = 1
} ; 

typedef enum {
    FREQ_8MHZ    = 8000000,   // PLL x2
    FREQ_12MHZ   = 12000000,  // PLL x3
    FREQ_16MHZ   = 16000000,  // PLL x4
    FREQ_20MHZ   = 20000000,  // PLL x5
    FREQ_24MHZ   = 24000000,  // PLL x6
    FREQ_28MHZ   = 28000000,  // PLL x7
    FREQ_32MHZ   = 32000000,  // PLL x8
    FREQ_36MHZ   = 36000000,  // PLL x9
    FREQ_40MHZ   = 40000000,  // PLL x10
    FREQ_44MHZ   = 44000000,  // PLL x11
    FREQ_48MHZ   = 48000000,  // PLL x12
    FREQ_52MHZ   = 52000000,  // PLL x13
    FREQ_56MHZ   = 56000000,  // PLL x14
    FREQ_60MHZ   = 60000000,  // PLL x15
    FREQ_64MHZ   = 64000000,   // PLL x16 (Tối đa của HSI)
    FREQ_72MHZ   = 72000000   // PLL x18 (Tối đa của HSE)   
} FREQ_Frequency_t;


typedef enum {
    ADC_CLOCK_DIV_2 = 0,
    ADC_CLOCK_DIV_4,
    ADC_CLOCK_DIV_6,
    ADC_CLOCK_DIV_8
} ADC_ClockPrescaler_t;

typedef enum {
    PPRE_CLOCK_DIV_1 = 0,
    PPRE_CLOCK_DIV_2 = 4,
    PPRE_CLOCK_DIV_4,
    PPRE_CLOCK_DIV_8,
    PPRE_CLOCK_DIV_16
}PPRE_Prescaler_t;     

typedef enum {
    HPRE_CLOCK_DIV_1 = 0,
    HPRE_CLOCK_DIV_2 = 8,
    HPRE_CLOCK_DIV_4,
    HPRE_CLOCK_DIV_8,
    HPRE_CLOCK_DIV_16,
    HPRE_CLOCK_DIV_64,
    HPRE_CLOCK_DIV_128,
    HPRE_CLOCK_DIV_256,
    HPRE_CLOCK_DIV_512
}HPRE_Prescaler_t;

typedef struct {
    ADC_ClockPrescaler_t ADC_Prescaler ;
    PPRE_Prescaler_t PPRE1_Prescaler;
    PPRE_Prescaler_t PPRE2_Prescaler;
    HPRE_Prescaler_t HPRE_Prescaler;
}RCC_ClockPrescaler_t;

typedef enum {
    AHB_Prescaler = 0,
    APB1_Prescaler,
    APB2_Prescaler,
    ADC_Prescaler
} RCC_Prescaler_t;


typedef struct 
{
    Source_Clock_t source_clock;
    FREQ_Frequency_t frequency;
    
}RCC_config_t;
typedef enum {
    RCC_OK = 0,
    RCC_NOT_OK = 1,
    RCC_ERROR_INVALID_PARAM = 2,
    RCCError_tIMEOUT = 3
} RCCError_t;

#define RCC_BASE_HANDMADE 	0x40021000UL
#define RCC_HANDMADE  		((volatile RCC_Handmade_t*)RCC_BASE_HANDMADE)

#define HSE_REQUIRED_FOR_72MHZ

RCCError_t init_RCC(RCC_config_t *RCC_config);
RCCError_t Select_Frequency_CLK(FREQ_Frequency_t Frequency_clk);
RCCError_t Select_Sources_Clock(Source_Clock_t Source_Clock);
RCCError_t Enable_Clock_RCC_APB2(APB2_Peripheral_Clock Peripheral_CLK);
RCCError_t Enable_Clock_RCC_APB1(APB1_Peripheral_Clock Peripheral_CLK);
RCCError_t Enable_Clock_RCC_AHB(AHB_Peripheral_Clock Peripheral_CLK);
RCCError_t Select_Prescaler_RCC(RCC_ClockPrescaler_t *Prescaler, RCC_Prescaler_t Prescaler_type);
FREQ_Frequency_t getFrequencyAPB1(void);
FREQ_Frequency_t getFrequencyAPB2(void);
FREQ_Frequency_t getFrequencyAHB(void);
FREQ_Frequency_t getFrequencyRCC(void);

#endif // GCC_HANDMADE_H
