#ifndef UART_HANDMADE_H
#define UART_HANDMADE_H
#include "stdint.h"
#include "RCC_Handmade.h"
#include "GPIO_Handmade.h"
#include "NVIC_Handmade.h"

// Cấu trúc ánh xạ thanh ghi UART (USART)
typedef struct {
    volatile uint32_t UART_SR;   // 0x00 - Status Register (SR)
    volatile uint32_t UART_DR;   // 0x04 - Data Register (DR)
    volatile uint32_t UART_BRR;  // 0x08 - Baud Rate Register (BRR)
    volatile uint32_t UART_CR1;  // 0x0C - Control Register 1 (CR1)
    volatile uint32_t UART_CR2;  // 0x10 - Control Register 2 (CR2)
    volatile uint32_t UART_CR3;  // 0x14 - Control Register 3 (CR3)
    volatile uint32_t UART_GTPR; // 0x18 - Guard Time and Prescaler Register (GTPR)
} UART_Handmade_t;

// Base address của các USART trên STM32F103
#define USART1_BASE_ADDRESS  0x40013800UL
#define USART2_BASE_ADDRESS  0x40004400UL
#define USART3_BASE_ADDRESS  0x40004800UL

// Con trỏ ánh xạ đến thanh ghi của từng USART
#define USART1_HANDMADE  ((volatile UART_Handmade_t*)USART1_BASE_ADDRESS)
#define USART2_HANDMADE  ((volatile UART_Handmade_t*)USART2_BASE_ADDRESS)
#define USART3_HANDMADE  ((volatile UART_Handmade_t*)USART3_BASE_ADDRESS)
	

typedef enum {
    UART_1 = 0,
    UART_2,
    UART_3
}UART_Type_t;

typedef enum {
    Custom_Baud_300 = 300,       // 300 baud
    Custom_Baud_600 = 600,       // 600 baud
    Custom_Baud_1200 = 1200,     // 1200 baud
    Custom_Baud_2400 = 2400,     // 2400 baud
    Custom_Baud_4800 = 4800,     // 4800 baud
    Custom_Baud_9600 = 9600,     // 9600 baud
    Custom_Baud_14400 = 14400,   // 14400 baud
    Custom_Baud_19200 = 19200,   // 19200 baud
    Custom_Baud_38400 = 38400,   // 38400 baud
    Custom_Baud_57600 = 57600,   // 57600 baud
    Custom_Baud_115200 = 115200, // 115200 baud
    Custom_Baud_230400 = 230400, // 230400 baud
    Custom_Baud_460800 = 460800, // 460800 baud
    Custom_Baud_921600 = 921600  // 921600 baud
} Custom_UART_BaudRate;

// CTS flag (Bit 9)
typedef enum {
    Custom_CTS_NO_CHANGE = 0x00, // No change on CTS line
    Custom_CTS_CHANGED = 0x01    // Change occurred on CTS line
} Custom_USART_SR_CTS;

// LIN break detection flag (Bit 8)
typedef enum {
    Custom_LBD_NO_BREAK = 0x00, // LIN break not detected
    Custom_LBD_BREAK = 0x01     // LIN break detected
} Custom_USART_SR_LBD;

// Transmit data register empty (Bit 7)
typedef enum {
    Custom_TXE_NOT_EMPTY = 0x00, // Data not transferred to shift register
    Custom_TXE_EMPTY = 0x01      // Data transferred to shift register
} Custom_USART_SR_TXE;

// Transmission complete (Bit 6)
typedef enum {
    Custom_TC_NOT_COMPLETE = 0x00, // Transmission not complete
    Custom_TC_COMPLETE = 0x01      // Transmission complete
} Custom_USART_SR_TC;

// Read data register not empty (Bit 5)
typedef enum {
    Custom_RXNE_EMPTY = 0x00, // Data not received
    Custom_RXNE_NOT_EMPTY = 0x01 // Received data ready to read
} Custom_USART_SR_RXNE;

// IDLE line detected (Bit 4)
typedef enum {
    Custom_IDLE_NOT_DETECTED = 0x00, // No idle line detected
    Custom_IDLE_DETECTED = 0x01      // Idle line detected
} Custom_USART_SR_IDLE;

// Overrun error (Bit 3)
typedef enum {
    Custom_ORE_NO_ERROR = 0x00, // No overrun error
    Custom_ORE_ERROR = 0x01     // Overrun error detected
} Custom_USART_SR_ORE;

// Noise error flag (Bit 2)
typedef enum {
    Custom_NE_NO_NOISE = 0x00, // No noise detected
    Custom_NE_NOISE = 0x01     // Noise detected
} Custom_USART_SR_NE;

// Framing error (Bit 1)
typedef enum {
    Custom_FE_NO_ERROR = 0x00, // No framing error
    Custom_FE_ERROR = 0x01     // Framing error or break detected
} Custom_USART_SR_FE;

// Parity error (Bit 0)
typedef enum {
    Custom_PE_NO_ERROR = 0x00, // No parity error
    Custom_PE_ERROR = 0x01     // Parity error detected
} Custom_USART_SR_PE;

// Prescaler value for USART_GTPR (PSC[7:0])
typedef enum {
    // Common values for IrDA and Smartcard
    Custom_PSC_DIV_1 = 0x01,  // Divide source clock by 1 (IrDA normal mode must use this)
    Custom_PSC_DIV_2 = 0x02,  // Divide source clock by 2
    Custom_PSC_DIV_4 = 0x04,  // Divide source clock by 4 (Smartcard: PSC[4:0] = 2)
    Custom_PSC_DIV_6 = 0x06,  // Divide source clock by 6 (Smartcard: PSC[4:0] = 3)
    Custom_PSC_DIV_8 = 0x08,  // Divide source clock by 8 (Smartcard: PSC[4:0] = 4)
    Custom_PSC_DIV_10 = 0x0A, // Divide source clock by 10 (Smartcard: PSC[4:0] = 5)
    Custom_PSC_DIV_12 = 0x0C, // Divide source clock by 12 (Smartcard: PSC[4:0] = 6)
    Custom_PSC_DIV_16 = 0x10, // Divide source clock by 16 (Smartcard: PSC[4:0] = 8)
    Custom_PSC_DIV_20 = 0x14, // Divide source clock by 20 (Smartcard: PSC[4:0] = 10)
    // Add more as needed
} Custom_USART_GTPR_PSC;


// Parameter of CR1 register
// USART enable (UE)
typedef enum {
    Custom_UE_DISABLE = 0x00, // USART prescaler and outputs disabled
    Custom_UE_ENABLE = 0x01  // USART enabled
} Custom_USART_CR1_UE;

// Word length (M)
typedef enum {
    Custom_M_8BIT = 0x00, // 1 Start bit, 8 Data bits
    Custom_M_9BIT = 0x01  // 1 Start bit, 9 Data bits
} Custom_USART_CR1_M;

// Wakeup method (WAKE)
typedef enum {
    Custom_WAKE_IDLE = 0x00, // Idle Line
    Custom_WAKE_ADDRESS = 0x01 // Address Mark
} Custom_USART_CR1_WAKE;

// Parity control enable (PCE)
typedef enum {
    Custom_PCE_DISABLE = 0x00, // Parity control disabled
    Custom_PCE_ENABLE = 0x01  // Parity control enabled
} Custom_USART_CR1_PCE;

// Parity selection (PS)
typedef enum {
    Custom_PS_EVEN = 0x00, // Even parity
    Custom_PS_ODD = 0x01  // Odd parity
} Custom_USART_CR1_PS;

// Interrupt enables (PEIE, TXEIE, TCIE, RXNEIE, IDLEIE)
typedef enum {
    Custom_INT_DISABLE = 0x00, // Interrupt inhibited
    Custom_INT_ENABLE = 0x01  // Interrupt enabled
} Custom_USART_CR1_INT;

// Transmitter enable (TE)
typedef enum {
    Custom_TE_DISABLE = 0x00, // Transmitter disabled
    Custom_TE_ENABLE = 0x01  // Transmitter enabled
} Custom_USART_CR1_TE;

// Receiver enable (RE)
typedef enum {
    Custom_RE_DISABLE = 0x00, // Receiver disabled
    Custom_RE_ENABLE = 0x01  // Receiver enabled
} Custom_USART_CR1_RE;

// Receiver wakeup (RWU)
typedef enum {
    Custom_RWU_ACTIVE = 0x00, // Receiver in active mode
    Custom_RWU_MUTE = 0x01   // Receiver in mute mode
} Custom_USART_CR1_RWU;

// Send break (SBK)
typedef enum {
    Custom_SBK_NO_BREAK = 0x00, // No break character transmitted
    Custom_SBK_BREAK = 0x01    // Break character transmitted
} Custom_USART_CR1_SBK;


// Parameter of CR2 register
// LIN mode enable (LINEN)
typedef enum {
    Custom_LINEN_DISABLE = 0x00, // LIN mode disabled
    Custom_LINEN_ENABLE = 0x01  // LIN mode enabled
} Custom_USART_CR2_LINEN;

// Stop bits (STOP[1:0])
typedef enum {
    Custom_STOP_1 = 0x00,    // 1 Stop bit
    Custom_STOP_0_5 = 0x01,  // 0.5 Stop bit
    Custom_STOP_2 = 0x02,    // 2 Stop bits
    Custom_STOP_1_5 = 0x03  // 1.5 Stop bit
} Custom_USART_CR2_STOP;

// Clock enable (CLKEN)
typedef enum {
    Custom_CLKEN_DISABLE = 0x00, // CK pin disabled
    Custom_CLKEN_ENABLE = 0x01  // CK pin enabled
} Custom_USART_CR2_CLKEN;

// Clock polarity (CPOL)
typedef enum {
    Custom_CPOL_LOW = 0x00,  // Steady low on CK pin
    Custom_CPOL_HIGH = 0x01 // Steady high on CK pin
} Custom_USART_CR2_CPOL;

// Clock phase (CPHA)
typedef enum {
    Custom_CPHA_FIRST = 0x00,  // First clock transition is capture edge
    Custom_CPHA_SECOND = 0x01 // Second clock transition is capture edge
} Custom_USART_CR2_CPHA;

// Last bit clock pulse (LBCL)
typedef enum {
    Custom_LBCL_NO_PULSE = 0x00, // No clock pulse for last bit
    Custom_LBCL_PULSE = 0x01    // Clock pulse for last bit
} Custom_USART_CR2_LBCL;

// LIN break detection interrupt enable (LBDIE)
typedef enum {
    Custom_LBDIE_DISABLE = 0x00, // Interrupt inhibited
    Custom_LBDIE_ENABLE = 0x01  // Interrupt enabled
} Custom_USART_CR2_LBDIE;

// LIN break detection length (LBDL)
typedef enum {
    Custom_LBDL_10BIT = 0x00, // 10 bit break detection
    Custom_LBDL_11BIT = 0x01 // 11 bit break detection
} Custom_USART_CR2_LBDL;



// Parameter of CR3 register
// CTS interrupt enable (CTSIE)
typedef enum {
    Custom_CTSIE_DISABLE = 0x00, // Interrupt inhibited
    Custom_CTSIE_ENABLE = 0x01  // Interrupt enabled
} Custom_USART_CR3_CTSIE;

// CTS enable (CTSE)
typedef enum {
    Custom_CTSE_DISABLE = 0x00, // CTS hardware flow control disabled
    Custom_CTSE_ENABLE = 0x01  // CTS mode enabled
} Custom_USART_CR3_CTSE;

// RTS enable (RTSE)
typedef enum {
    Custom_RTSE_DISABLE = 0x00, // RTS hardware flow control disabled
    Custom_RTSE_ENABLE = 0x01  // RTS interrupt enabled
} Custom_USART_CR3_RTSE;

// DMA enable transmitter (DMAT)
typedef enum {
    Custom_DMAT_DISABLE = 0x00, // DMA mode disabled for transmission
    Custom_DMAT_ENABLE = 0x01  // DMA mode enabled for transmission
} Custom_USART_CR3_DMAT;

// DMA enable receiver (DMAR)
typedef enum {
    Custom_DMAR_DISABLE = 0x00, // DMA mode disabled for reception
    Custom_DMAR_ENABLE = 0x01  // DMA mode enabled for reception
} Custom_USART_CR3_DMAR;

// Smartcard mode enable (SCEN)
typedef enum {
    Custom_SCEN_DISABLE = 0x00, // Smartcard mode disabled
    Custom_SCEN_ENABLE = 0x01  // Smartcard mode enabled
} Custom_USART_CR3_SCEN;

// Smartcard NACK enable (NACK)
typedef enum {
    Custom_NACK_DISABLE = 0x00, // NACK transmission disabled
    Custom_NACK_ENABLE = 0x01  // NACK transmission enabled
} Custom_USART_CR3_NACK;

// Half-duplex selection (HDSEL)
typedef enum {
    Custom_HDSEL_DISABLE = 0x00, // Half duplex mode not selected
    Custom_HDSEL_ENABLE = 0x01  // Half duplex mode selected
} Custom_USART_CR3_HDSEL;

// IrDA low-power (IRLP)
typedef enum {
    Custom_IRLP_NORMAL = 0x00, // Normal mode
    Custom_IRLP_LOW_POWER = 0x01 // Low-power mode
} Custom_USART_CR3_IRLP;

// IrDA mode enable (IREN)
typedef enum {
    Custom_IREN_DISABLE = 0x00, // IrDA disabled
    Custom_IREN_ENABLE = 0x01  // IrDA enabled
} Custom_USART_CR3_IREN;

// Error interrupt enable (EIE)
typedef enum {
    Custom_EIE_DISABLE = 0x00, // Interrupt inhibited
    Custom_EIE_ENABLE = 0x01  // Interrupt enabled
} Custom_USART_CR3_EIE;

typedef enum {
    UART_OK = 0,        // Không có lỗi
    UART_ERROR = 1,     // Lỗi chung
    UART_NULL_PTR = 2,  // Con trỏ NULL
    UART_INVALID_PARAM = 3, // Tham số không hợp lệ
    UART_NO_DATA,
    UART_NOT_READY
} Error_UART_t;


typedef struct {
    UART_Type_t USARTx; // Con trỏ hoặc chỉ số tới USART (thay bằng định nghĩa thực tế)

    // USART_CR1
    Custom_USART_CR1_UE usartEnable;        // UE: USART enable
    Custom_USART_CR1_M wordLength;          // M: Word length
    Custom_USART_CR1_WAKE wakeupMethod;     // WAKE: Wakeup method
    Custom_USART_CR1_PCE parityControl;     // PCE: Parity control enable
    Custom_USART_CR1_PS paritySelection;    // PS: Parity selection
    Custom_USART_CR1_INT peInterrupt;       // PEIE: Parity error interrupt
    Custom_USART_CR1_INT txeInterrupt;      // TXEIE: Transmit data empty interrupt
    Custom_USART_CR1_INT tcInterrupt;       // TCIE: Transmission complete interrupt
    Custom_USART_CR1_INT rxneInterrupt;     // RXNEIE: Receive data not empty interrupt
    Custom_USART_CR1_INT idleInterrupt;     // IDLEIE: IDLE line interrupt
    Custom_USART_CR1_TE transmitterEnable;  // TE: Transmitter enable
    Custom_USART_CR1_RE receiverEnable;     // RE: Receiver enable
    Custom_USART_CR1_RWU receiverWakeup;    // RWU: Receiver wakeup
    Custom_USART_CR1_SBK sendBreak;         // SBK: Send break

    // USART_CR2
    Custom_USART_CR2_LINEN linMode;         // LINEN: LIN mode enable
    Custom_USART_CR2_STOP stopBits;         // STOP: Stop bits
    Custom_USART_CR2_CLKEN clockEnable;     // CLKEN: Clock enable
    Custom_USART_CR2_CPOL clockPolarity;    // CPOL: Clock polarity
    Custom_USART_CR2_CPHA clockPhase;       // CPHA: Clock phase
    Custom_USART_CR2_LBCL lastBitClock;     // LBCL: Last bit clock pulse
    Custom_USART_CR2_LBDIE linBreakInterrupt; // LBDIE: LIN break detection interrupt
    Custom_USART_CR2_LBDL linBreakLength;   // LBDL: LIN break detection length
    uint8_t nodeAddress;                    // ADD[3:0]: Address of USART node (0-15)

    // USART_CR3
    Custom_USART_CR3_CTSIE ctsInterrupt;    // CTSIE: CTS interrupt enable
    Custom_USART_CR3_CTSE ctsEnable;        // CTSE: CTS enable
    Custom_USART_CR3_RTSE rtsEnable;        // RTSE: RTS enable
    Custom_USART_CR3_DMAT dmaTransmitter;   // DMAT: DMA enable transmitter
    Custom_USART_CR3_DMAR dmaReceiver;      // DMAR: DMA enable receiver
    Custom_USART_CR3_SCEN smartcardMode;    // SCEN: Smartcard mode enable
    Custom_USART_CR3_NACK smartcardNack;    // NACK: Smartcard NACK enable
    Custom_USART_CR3_HDSEL halfDuplex;      // HDSEL: Half-duplex selection
    Custom_USART_CR3_IRLP irdaLowPower;     // IRLP: IrDA low-power
    Custom_USART_CR3_IREN irdaMode;         // IREN: IrDA mode enable
    Custom_USART_CR3_EIE errorInterrupt;    // EIE: Error interrupt enable

    // USART_BRR (Baud rate configuration)
    Custom_UART_BaudRate baudUART;

    // USART_GTPR (Guard time and prescaler)
    uint8_t guardTime;                      // GT[7:0]: Guard time value (0-255, Smartcard)
    Custom_USART_GTPR_PSC prescalerValue;   // PSC[7:0]: Prescaler value (IrDA/Smartcard)

    // USART_SR (Status flags for monitoring, optional)
    Custom_USART_SR_CTS ctsStatus;          // CTS: CTS flag
    Custom_USART_SR_LBD linBreakStatus;     // LBD: LIN break detection flag
    Custom_USART_SR_TXE transmitEmpty;      // TXE: Transmit data register empty
    Custom_USART_SR_TC transmitComplete;    // TC: Transmission complete
    Custom_USART_SR_RXNE receiveNotEmpty;   // RXNE: Read data register not empty
    Custom_USART_SR_IDLE idleDetected;      // IDLE: IDLE line detected
    Custom_USART_SR_ORE overrunError;       // ORE: Overrun error
    Custom_USART_SR_NE noiseError;          // NE: Noise error flag
    Custom_USART_SR_FE framingError;        // FE: Framing error
    Custom_USART_SR_PE parityError;         // PE: Parity error
} Custom_USART_Config_t;


Error_UART_t UARTInit(Custom_USART_Config_t *uartConfig);
Error_UART_t TransmitDataUART(UART_Type_t UARTx,uint8_t *Data,uint8_t lengthData);
Error_UART_t ReceiveDataUART(UART_Type_t UARTx,uint8_t *Data,uint8_t lengthData);
Error_UART_t EnableInterrupt_RX_UARTx(UART_Type_t uartx);
Error_UART_t ReceiveDataUART_IT(UART_Type_t uartx,uint8_t *Buffer,uint8_t length);
void interruptEnable(UART_Type_t uartx);
void interruptDisable(UART_Type_t uartx);

#endif // UART_HANDMADE_H



