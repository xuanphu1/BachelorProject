#ifndef GPIO_HANDMADE_H
#define GPIO_HANDMADE_H
#include "stdio.h"
#include "stdint.h"
#include "RCC_Handmade.h"

typedef struct {
    
    uint32_t GPIO_CRL ;
    uint32_t GPIO_CRH ;
    uint32_t GPIO_IDR ;
    uint32_t GPIO_ODR ;
    uint32_t GPIO_BSRR ;
    uint32_t GPIO_BRR ;
    uint32_t GPIO_LCKR ;
}GPIO_Handmade_t ;

typedef struct 
{
    uint32_t EVCR;
    uint32_t MAPR;
    uint32_t EXTICR1;
    uint32_t EXTICR2;
    uint32_t EXTICR3;
    uint32_t EXTICR4;
    uint32_t MAPR2;
}AFIO_Handmade_t;


#define GPIOA_BASE_HANDMADE 0x40010800UL
#define GPIOB_BASE_HANDMADE 0x40010C00UL
#define GPIOC_BASE_HANDMADE 0x40011000UL
#define GPIOD_BASE_HANDMADE 0x40011400UL
#define GPIOE_BASE_HANDMADE 0x40011800UL
#define GPIOF_BASE_HANDMADE 0x40011C00UL
#define GPIOG_BASE_HANDMADE 0x40012000UL


#define GPIOA_HANDMADE ((volatile GPIO_Handmade_t*)GPIOA_BASE_HANDMADE)
#define GPIOB_HANDMADE ((volatile GPIO_Handmade_t*)GPIOB_BASE_HANDMADE)
#define GPIOC_HANDMADE ((volatile GPIO_Handmade_t*)GPIOC_BASE_HANDMADE)
#define GPIOD_HANDMADE ((volatile GPIO_Handmade_t*)GPIOD_BASE_HANDMADE)
#define GPIOE_HANDMADE ((volatile GPIO_Handmade_t*)GPIOE_BASE_HANDMADE)
#define GPIOF_HANDMADE ((volatile GPIO_Handmade_t*)GPIOF_BASE_HANDMADE)
#define GPIOG_HANDMADE ((volatile GPIO_Handmade_t*)GPIOG_BASE_HANDMADE)

#define AFIO_BASE_HANDMADE 0x40010000UL
#define AFIO_HANDMADE ((volatile AFIO_Handmade_t*)AFIO_BASE_HANDMADE)


typedef enum {
    Port_A = 0,
    Port_B,
    Port_C,
    Port_D,
    Port_E,
    Port_F,
    Port_G
}Port_t;



typedef enum {
    CNF_MODE_00 = 0,
    CNF_MODE_01,
    CNF_MODE_10,
    CNF_MODE_11
}CNF_Mode_t;


typedef enum {
    INPUT_MODE = 0,
    OUTPUT_MODE_10_MHZ,
    OUTPUT_MODE_2_MHZ,
    OUTPUT_MODE_50_MHZ
}Mode_Pin_t;

typedef enum {
    PIN_0 = 0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7,
    PIN_8,
    PIN_9,
    PIN_10,
    PIN_11,
    PIN_12,
    PIN_13,
    PIN_14,
    PIN_15
}Pin_gpio_t;


typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH

}State_Pin_t;


typedef struct
{
    Port_t port;
    Pin_gpio_t pin;
    CNF_Mode_t cnf_mode;
    Mode_Pin_t mode;

}GPIO_config_t;

typedef enum {
    GPIO_OK = 0,
    GPIO_NOT_OK = 1,
    GPIO_ERROR_INVALID_PARAM = 2,
    GPIO_ERROR_NOT_INITIALIZED = 3
} GPIO_Error_t;

GPIO_Error_t InitGPIO(GPIO_config_t *config_gpio);
uint32_t ReadPin(Port_t port,Pin_gpio_t Pin);
GPIO_Error_t WritePin(Port_t port, Pin_gpio_t Pin, uint32_t value);
GPIO_Error_t TogglePin(Port_t port, Pin_gpio_t Pin);
GPIO_Error_t WriteMultiPins(Port_t port, uint32_t pin_mask, uint32_t value);
GPIO_Error_t ReadMultiPins(Port_t port, Pin_gpio_t *pins, uint8_t *output_array, uint8_t pin_count);
GPIO_Error_t enableSWD(void);

void ON_Led_Hardware(void);
void OFF_Led_Hardware(void);

#endif // GPIO_HANDMADE_H










