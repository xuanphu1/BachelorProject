#ifndef ADC_HANDMADE_H
#define ADC_HANDMADE_H

#include "stdint.h"
#include "RCC_Handmade.h"
#include "GPIO_Handmade.h"

// Cấu trúc thanh ghi ADC STM32F103
typedef struct {
    volatile uint32_t ADC_SR;
    volatile uint32_t ADC_CR1;
    volatile uint32_t ADC_CR2;
    volatile uint32_t ADC_SMPR1;
    volatile uint32_t ADC_SMPR2;
    volatile uint32_t ADC_JOFR1;
    volatile uint32_t ADC_JOFR2;
    volatile uint32_t ADC_JOFR3;
    volatile uint32_t ADC_JOFR4;
    volatile uint32_t ADC_HTR;
    volatile uint32_t ADC_LTR;
    volatile uint32_t ADC_SQR1;
    volatile uint32_t ADC_SQR2;
    volatile uint32_t ADC_SQR3;
    volatile uint32_t ADC_JSQR;
    volatile uint32_t ADC_JDR1;
    volatile uint32_t ADC_JDR2;
    volatile uint32_t ADC_JDR3;
    volatile uint32_t ADC_JDR4;
    volatile uint32_t ADC_DR;
} ADC_Handmade_t;

#define ADC1_BASE_ADDRESS  0x40012400UL
#define ADC1_HANDMADE               ((volatile ADC_Handmade_t*)ADC1_BASE_ADDRESS)



// Enum ADC channel
typedef enum {
    CUSTOM_ADC_CHANNEL_0 = 0,
    CUSTOM_ADC_CHANNEL_1,
    CUSTOM_ADC_CHANNEL_2,
    CUSTOM_ADC_CHANNEL_3,
    CUSTOM_ADC_CHANNEL_4,
    CUSTOM_ADC_CHANNEL_5,
    CUSTOM_ADC_CHANNEL_6,
    CUSTOM_ADC_CHANNEL_7,
    CUSTOM_ADC_CHANNEL_8,
    CUSTOM_ADC_CHANNEL_9,
    CUSTOM_ADC_CHANNEL_10,
    CUSTOM_ADC_CHANNEL_11,
    CUSTOM_ADC_CHANNEL_12,
    CUSTOM_ADC_CHANNEL_13,
    CUSTOM_ADC_CHANNEL_14,
    CUSTOM_ADC_CHANNEL_15,
    CUSTOM_ADC_CHANNEL_TEMP_SENSOR,
    CUSTOM_ADC_CHANNEL_VREFINT
} ADC_Channel_t;

// Thời gian lấy mẫu ADC
typedef enum {
    SAMPLE_1_5_CYCLES = 0,
    SAMPLE_7_5_CYCLES,
    SAMPLE_13_5_CYCLES,
    SAMPLE_28_5_CYCLES,
    SAMPLE_41_5_CYCLES,
    SAMPLE_55_5_CYCLES,
    SAMPLE_71_5_CYCLES,
    SAMPLE_239_5_CYCLES
} ADC_SampleTime_t;

// Chế độ chuyển đổi ADC
typedef enum {
    SINGLE_CONVERSION = 0,
    CONTINUOUS_CONVERSION
} ADC_ConversionMode_t;

typedef enum {
    SCAN_DISABLE = 0,
    SCAN_ENABLE
}ADC_ScanMode_t;


// DMA Mode
typedef enum {
    DMA_DISABLE = 0,
    DMA_ENABLE
} ADC_DMA_Mode_t;

// ADC Data Alignment
typedef enum {
    DATAALIGN_RIGHT = 0,
    DATAALIGN_LEFT
} ADC_DataAlign_t;

// External Trigger
typedef enum {
    EXTERNAL_TRIGGER_DISABLE = 0,
    EXTERNAL_TRIGGER_ENABLE
} ADC_ExternalTrigger_t;

// Interrupt Mode
typedef enum {
    INTERRUPT_DISABLE = 0,
    INTERRUPT_ENABLE
} ADC_InterruptMode_t;

// Bộ chia Clock cho ADC
typedef enum {
    CLOCK_ADC_DIV_2 = 0,
    CLOCK_ADC_DIV_4,
    CLOCK_ADC_DIV_6,
    CLOCK_ADC_DIV_8
} ClockPrescaler_t;

// Cấu hình ADC
typedef struct {
    ADC_ScanMode_t scan_mode;
    ADC_DMA_Mode_t dma_mode;
    ADC_ConversionMode_t conversion_mode;
    ADC_DataAlign_t data_align;
    ADC_ExternalTrigger_t external_trigger;
    ADC_InterruptMode_t interrupt_mode;
    ADC_ClockPrescaler_t clock_prescaler;
    ADC_Channel_t RegularSequence[16];
    uint8_t num_of_conversions;
    ADC_SampleTime_t sample_time;
    uint16_t Result_ADC[16];
} ADC_Config_t;


typedef enum {
    ADC_OK = 0,
    ADC_NOT_OK = 1,
    ADC_ERROR_INVALID_PARAM = 2,
    ADC_ERROR_TIMEOUT = 3,
    ADC_ERROR_NOT_INITIALIZED = 4
} ADC_Error_t;

// Hàm cập nhật với kiểu trả về
ADC_Error_t ADC_EnableClock(ADC_ClockPrescaler_t prescaler);
ADC_Error_t ADC_Init(ADC_Config_t *adcConfig);
ADC_Error_t ADC_ReadMultiple(ADC_Config_t *adcConfig);
ADC_Error_t ADC_DMA_Start(void);
#endif // ADC_HANDMADE_H


