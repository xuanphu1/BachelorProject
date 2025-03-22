#ifndef DMA_HANDMADE_H
#define DMA_HANDMADE_H
#include "stdint.h"
#include "RCC_Handmade.h"


typedef struct {
    volatile uint32_t DMA_CCR;      // 0x00 - DMA Channel Configuration Register
    volatile uint32_t DMA_CNDTR;    // 0x04 - DMA Channel Number of Data Register
    volatile uint32_t DMA_CPAR;     // 0x08 - DMA Channel Peripheral Address Register
    volatile uint32_t DMA_CMAR;     // 0x0C - DMA Channel Memory Address Register
    volatile uint32_t RESERVED;     // 0x10 - Reserved (offset 0x14)
} DMA_Channel_t;



typedef struct {
    volatile uint32_t DMA_ISR;       // 0x00 - DMA Interrupt Status Register
    volatile uint32_t DMA_IFCR;      // 0x04 - DMA Interrupt Flag Clear Register  // 0x08 - DMA Channel 1 Configuration Register
    DMA_Channel_t CHANNEL[7];        // 7 Kênh DMA độc lập
} DMA_Handmade_t;

#define DMA1_BASE_ADDRESS 0x40020000UL
#define DMA1_HANDMADE ((volatile DMA_Handmade_t*)DMA1_BASE_ADDRESS)


typedef enum {
    DMA_LOW_PRIORITY       = 0x00,
    DMA_MEDIUM_PRIORITY    = 0x01,
    DMA_HIGH_PRIORITY      = 0x02,
    DMA_VERY_HIGH_PRIORITY = 0x03
} DMA_Priority_t;

typedef enum {
    DISABLE_DMA_PINC = 0x00,  // Không tăng địa chỉ ngoại vi sau mỗi lần truyền
    ENABLE_DMA_PINC  = 0x01   // Tăng địa chỉ ngoại vi sau mỗi lần truyền
} DMA_PeripheralInc_t;

typedef enum {
    DISABLE_DMA_MINC = 0x00,  // Không tăng địa chỉ bộ nhớ sau mỗi lần truyền
    ENABLE_DMA_MINC  = 0x01   // Tăng địa chỉ bộ nhớ sau mỗi lần truyền
} DMA_MemoryInc_t;

typedef enum {
    DMA_PSIZE_8BIT  = 0x00,  // Peripheral Size = 8-bit
    DMA_PSIZE_16BIT = 0x01,  // Peripheral Size = 16-bit
    DMA_PSIZE_32BIT = 0x02   // Peripheral Size = 32-bit
} DMA_PeripheralSize_t;

typedef enum {
    DMA_MSIZE_8BIT  = 0x00,  // Memory Size = 8-bit
    DMA_MSIZE_16BIT = 0x01,  // Memory Size = 16-bit
    DMA_MSIZE_32BIT = 0x02   // Memory Size = 32-bit
} DMA_MemorySize_t;

typedef enum {
    DMA_CIRC_DISABLE = 0x00,  // Không vòng lặp (Dừng sau khi truyền xong)
    DMA_CIRC_ENABLE  = 0x01   // Vòng lặp (Tự động reset counter, chạy liên tục)
} DMA_CircularMode_t;

typedef enum {
    DMA_DIR_PERIPH_TO_MEM = 0x00,  // Truyền dữ liệu từ Peripheral → Memory
    DMA_DIR_MEM_TO_PERIPH = 0x01   // Truyền dữ liệu từ Memory → Peripheral
} DMA_Direction_t;

typedef enum {
    DMA_TEIE_DISABLE = 0x00,  // Không kích hoạt ngắt lỗi
    DMA_TEIE_ENABLE  = 0x01   // Kích hoạt ngắt lỗi
} DMA_TransferErrorInt_t;

typedef enum {
    DMA_HTIE_DISABLE = 0x00,  // Không kích hoạt ngắt Half-Transfer
    DMA_HTIE_ENABLE  = 0x01   // Kích hoạt ngắt Half-Transfer
} DMA_HalfTransferInt_t;

typedef enum {
    DMA_TCIE_DISABLE = 0x00,  // Không kích hoạt ngắt Transfer Complete
    DMA_TCIE_ENABLE  = 0x01   // Kích hoạt ngắt Transfer Complete
} DMA_TransferCompleteInt_t;

typedef enum {
    DMA_CHANNEL_1 = 0x00,
    DMA_CHANNEL_2 = 0x01,
    DMA_CHANNEL_3 = 0x02,
    DMA_CHANNEL_4 = 0x03,
    DMA_CHANNEL_5 = 0x04,
    DMA_CHANNEL_6 = 0x05,
    DMA_CHANNEL_7 = 0x06
} DMAChannel_t;


typedef struct {
    DMAChannel_t Channel;
    DMA_Priority_t Priority;
    DMA_PeripheralInc_t PeripheralIncrement;
    DMA_MemoryInc_t MemoryIncrement;
    DMA_PeripheralSize_t PeripheralSize;
    DMA_MemorySize_t MemorySize;
    DMA_CircularMode_t CircularMode;
    DMA_Direction_t Direction;
    DMA_TransferErrorInt_t TransferErrorInt;
    DMA_HalfTransferInt_t HalfTransferInt;
    DMA_TransferCompleteInt_t TransferCompleteInt;
    uint32_t PeripheralAddress;
    uint32_t MemoryAddress;
    uint32_t NumData;
} DMA_Config_t;

typedef enum {
    DMA_OK = 0,
    DMA_ERROR_INVALID_PARAM = 1,
    DMA_ERROR_NOT_INITIALIZED = 2
} DMA_Error_t;

// Hàm cập nhật với kiểu trả về
DMA_Error_t DMA_Init(DMA_Config_t *dmaConfig);
DMA_Error_t DMA_Start(DMAChannel_t channel);
#endif // DMA_HANDMADE_H


