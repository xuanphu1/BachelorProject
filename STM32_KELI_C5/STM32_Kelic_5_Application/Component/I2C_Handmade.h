#ifndef _I2C_HANDMADE_H
#define _I2C_HANDMADE_H
#include "stdint.h"
#include "RCC_Handmade.h"
#include "GPIO_Handmade.h"




typedef struct {
    uint32_t CR1;
    uint32_t CR2;
    uint32_t OAR1;
    uint32_t OAR2;
    uint32_t DR;
    uint32_t SR1;
    uint32_t SR2;
    uint32_t CCR;
    uint32_t TRISE;
} I2C_Handmade_t;


typedef enum {
    I2C1 = 0,
    I2C2 = 1
} I2C_Type_t;




#define I2C1_BASE 0x40005400UL
#define I2C2_BASE 0x40005800UL


#define I2C1_HANDMADE ((volatile I2C_Handmade_t*)I2C1_BASE)
#define I2C2_HANDMADE ((volatile I2C_Handmade_t*)I2C2_BASE)


// --- I2C_CR1 (Control Register 1) ---
// Bit 15: SWRST
typedef enum {
    I2C_CR1_SWRST_NO_RESET = 0,  // I2C peripheral not under reset
    I2C_CR1_SWRST_RESET    = 1   // I2C peripheral under reset state
} I2C_CR1_SWRST_t;

// Bit 13: ALERT
typedef enum {
    I2C_CR1_ALERT_RELEASE = 0,   // Releases SMBA pin high
    I2C_CR1_ALERT_DRIVE   = 1    // Drives SMBA pin low
} I2C_CR1_ALERT_t;

// Bit 12: PEC
typedef enum {
    I2C_CR1_PEC_NO_TRANSFER = 0, // No PEC transfer
    I2C_CR1_PEC_TRANSFER    = 1  // PEC transfer
} I2C_CR1_PEC_t;

// Bit 11: POS
typedef enum {
    I2C_CR1_POS_CURRENT = 0,     // ACK/PEC for current byte
    I2C_CR1_POS_NEXT    = 1      // ACK/PEC for next byte
} I2C_CR1_POS_t;

// Bit 10: ACK
typedef enum {
    I2C_CR1_ACK_DISABLE = 0,     // No acknowledge returned
    I2C_CR1_ACK_ENABLE  = 1      // Acknowledge returned
} I2C_CR1_ACK_t;

// Bit 9: STOP
typedef enum {
    I2C_CR1_STOP_NO_GEN = 0,     // No Stop generation
    I2C_CR1_STOP_GEN    = 1      // Stop generation
} I2C_CR1_STOP_t;

// Bit 8: START
typedef enum {
    I2C_CR1_START_NO_GEN = 0,    // No Start generation
    I2C_CR1_START_GEN    = 1     // Start generation
} I2C_CR1_START_t;

// Bit 7: NOSTRETCH
typedef enum {
    I2C_CR1_NOSTRETCH_ENABLE  = 0, // Clock stretching enabled
    I2C_CR1_NOSTRETCH_DISABLE = 1  // Clock stretching disabled
} I2C_CR1_NOSTRETCH_t;

// Bit 6: ENGC
typedef enum {
    I2C_CR1_ENGC_DISABLE = 0,    // General call disabled
    I2C_CR1_ENGC_ENABLE  = 1     // General call enabled
} I2C_CR1_ENGC_t;

// Bit 5: ENPEC
typedef enum {
    I2C_CR1_ENPEC_DISABLE = 0,   // PEC calculation disabled
    I2C_CR1_ENPEC_ENABLE  = 1    // PEC calculation enabled
} I2C_CR1_ENPEC_t;

// Bit 4: ENARP
typedef enum {
    I2C_CR1_ENARP_DISABLE = 0,   // ARP disable
    I2C_CR1_ENARP_ENABLE  = 1    // ARP enable
} I2C_CR1_ENARP_t;

// Bit 3: SMBTYPE
typedef enum {
    I2C_CR1_SMBTYPE_DEVICE = 0,  // SMBus Device
    I2C_CR1_SMBTYPE_HOST   = 1   // SMBus Host
} I2C_CR1_SMBTYPE_t;

// Bit 1: SMBUS
typedef enum {
    I2C_CR1_SMBUS_I2C   = 0,     // I2C mode
    I2C_CR1_SMBUS_SMBUS = 1      // SMBus mode
} I2C_CR1_SMBUS_t;

// Bit 0: PE
typedef enum {
    I2C_CR1_PE_DISABLE = 0,      // Peripheral disable
    I2C_CR1_PE_ENABLE  = 1       // Peripheral enable
} I2C_CR1_PE_t;

// --- I2C_CR2 (Control Register 2) ---
// Bit 12: LAST
typedef enum {
    I2C_CR2_LAST_NOT_LAST = 0,   // Next DMA EOT is not the last transfer
    I2C_CR2_LAST_IS_LAST  = 1    // Next DMA EOT is the last transfer
} I2C_CR2_LAST_t;

// Bit 11: DMAEN
typedef enum {
    I2C_CR2_DMAEN_DISABLE = 0,   // DMA requests disabled
    I2C_CR2_DMAEN_ENABLE  = 1    // DMA requests enabled
} I2C_CR2_DMAEN_t;

// Bit 10: ITBUFEN
typedef enum {
    I2C_CR2_ITBUFEN_DISABLE = 0, // Buffer interrupt disabled
    I2C_CR2_ITBUFEN_ENABLE  = 1  // Buffer interrupt enabled
} I2C_CR2_ITBUFEN_t;

// Bit 9: ITEVTEN
typedef enum {
    I2C_CR2_ITEVTEN_DISABLE = 0, // Event interrupt disabled
    I2C_CR2_ITEVTEN_ENABLE  = 1  // Event interrupt enabled
} I2C_CR2_ITEVTEN_t;

// Bit 8: ITERREN
typedef enum {
    I2C_CR2_ITERREN_DISABLE = 0, // Error interrupt disabled
    I2C_CR2_ITERREN_ENABLE  = 1  // Error interrupt enabled
} I2C_CR2_ITERREN_t;

// Bits 5:0: FREQ[5:0] (giá trị tiêu biểu)
typedef enum {
    I2C_CR2_FREQ_2MHZ  = 0x02,   // 2 MHz
    I2C_CR2_FREQ_8MHZ  = 0x08,   // 8 MHz (ví dụ trong tài liệu)
    I2C_CR2_FREQ_10MHZ = 0x0A,   // 10 MHz
    I2C_CR2_FREQ_50MHZ = 0x32    // 50 MHz (tối đa)
} I2C_CR2_FREQ_t;

// --- I2C_OAR1 (Own Address Register 1) ---
// Bit 15: ADDMODE
typedef enum {
    I2C_OAR1_ADDMODE_7BIT  = 0,  // 7-bit addressing mode
    I2C_OAR1_ADDMODE_10BIT = 1   // 10-bit addressing mode
} I2C_OAR1_ADDMODE_t;

// --- I2C_OAR2 (Own Address Register 2) ---
// Bit 0: ENDUAL
typedef enum {
    I2C_OAR2_ENDUAL_SINGLE = 0,  // Only OAR1 recognized
    I2C_OAR2_ENDUAL_DUAL   = 1   // Both OAR1 and OAR2 recognized
} I2C_OAR2_ENDUAL_t;

// --- I2C_DR (Data Register) ---
// Không cần enum vì đây là giá trị dữ liệu 8-bit (0x00 - 0xFF)

// --- I2C_SR1 (Status Register 1) ---
// Bit 15: SMBALERT
typedef enum {
    I2C_SR1_SMBALERT_NO    = 0,  // No SMBus alert
    I2C_SR1_SMBALERT_YES   = 1   // SMBus alert occurred
} I2C_SR1_SMBALERT_t;

// Bit 14: TIMEOUT
typedef enum {
    I2C_SR1_TIMEOUT_NO     = 0,  // No timeout error
    I2C_SR1_TIMEOUT_YES    = 1   // Timeout or Tlow error
} I2C_SR1_TIMEOUT_t;

// Bit 12: PECERR
typedef enum {
    I2C_SR1_PECERR_NO      = 0,  // No PEC error
    I2C_SR1_PECERR_YES     = 1   // PEC error
} I2C_SR1_PECERR_t;

// Bit 11: OVR
typedef enum {
    I2C_SR1_OVR_NO         = 0,  // No overrun/underrun
    I2C_SR1_OVR_YES        = 1   // Overrun or underrun
} I2C_SR1_OVR_t;

// Bit 10: AF
typedef enum {
    I2C_SR1_AF_NO          = 0,  // No acknowledge failure
    I2C_SR1_AF_YES         = 1   // Acknowledge failure
} I2C_SR1_AF_t;

// Bit 9: ARLO
typedef enum {
    I2C_SR1_ARLO_NO        = 0,  // No arbitration lost
    I2C_SR1_ARLO_YES       = 1   // Arbitration lost
} I2C_SR1_ARLO_t;

// Bit 8: BERR
typedef enum {
    I2C_SR1_BERR_NO        = 0,  // No bus error
    I2C_SR1_BERR_YES       = 1   // Bus error
} I2C_SR1_BERR_t;

// Bit 7: TxE
typedef enum {
    I2C_SR1_TXE_NOT_EMPTY  = 0,  // Data register not empty
    I2C_SR1_TXE_EMPTY      = 1   // Data register empty
} I2C_SR1_TXE_t;

// Bit 6: RxNE
typedef enum {
    I2C_SR1_RXNE_EMPTY     = 0,  // Data register empty
    I2C_SR1_RXNE_NOT_EMPTY = 1   // Data register not empty
} I2C_SR1_RXNE_t;

// Bit 4: STOPF
typedef enum {
    I2C_SR1_STOPF_NO       = 0,  // No Stop condition detected
    I2C_SR1_STOPF_YES      = 1   // Stop condition detected
} I2C_SR1_STOPF_t;

// Bit 3: ADD10
typedef enum {
    I2C_SR1_ADD10_NO       = 0,  // No 10-bit header sent
    I2C_SR1_ADD10_YES      = 1   // 10-bit header sent
} I2C_SR1_ADD10_t;

// Bit 2: BTF
typedef enum {
    I2C_SR1_BTF_NOT_DONE   = 0,  // Byte transfer not done
    I2C_SR1_BTF_DONE       = 1   // Byte transfer succeeded
} I2C_SR1_BTF_t;

// Bit 1: ADDR
typedef enum {
    I2C_SR1_ADDR_NO        = 0,  // Address not matched/sent
    I2C_SR1_ADDR_YES       = 1   // Address matched/sent
} I2C_SR1_ADDR_t;

// Bit 0: SB
typedef enum {
    I2C_SR1_SB_NO          = 0,  // No Start condition
    I2C_SR1_SB_YES         = 1   // Start condition generated
} I2C_SR1_SB_t;

// --- I2C_SR2 (Status Register 2) ---
// Bit 7: DUALF
typedef enum {
    I2C_SR2_DUALF_OAR1     = 0,  // Address matched with OAR1
    I2C_SR2_DUALF_OAR2     = 1   // Address matched with OAR2
} I2C_SR2_DUALF_t;

// Bit 6: SMBHOST
typedef enum {
    I2C_SR2_SMBHOST_NO     = 0,  // No SMBus Host address
    I2C_SR2_SMBHOST_YES    = 1   // SMBus Host address received
} I2C_SR2_SMBHOST_t;

// Bit 5: SMBDEFAULT
typedef enum {
    I2C_SR2_SMBDEFAULT_NO  = 0,  // No SMBus Device Default address
    I2C_SR2_SMBDEFAULT_YES = 1   // SMBus Device Default address received
} I2C_SR2_SMBDEFAULT_t;

// Bit 4: GENCALL
typedef enum {
    I2C_SR2_GENCALL_NO     = 0,  // No General Call
    I2C_SR2_GENCALL_YES    = 1   // General Call Address received
} I2C_SR2_GENCALL_t;

// Bit 2: TRA
typedef enum {
    I2C_SR2_TRA_RECEIVER   = 0,  // Data bytes received
    I2C_SR2_TRA_TRANSMITTER = 1  // Data bytes transmitted
} I2C_SR2_TRA_t;

// Bit 1: BUSY
typedef enum {
    I2C_SR2_BUSY_NO        = 0,  // No communication on the bus
    I2C_SR2_BUSY_YES       = 1   // Communication ongoing on the bus
} I2C_SR2_BUSY_t;

// Bit 0: MSL
typedef enum {
    I2C_SR2_MSL_SLAVE      = 0,  // Slave mode
    I2C_SR2_MSL_MASTER     = 1   // Master mode
} I2C_SR2_MSL_t;

// --- I2C_CCR (Clock Control Register) ---
// Bit 15: F/S
typedef enum {
    I2C_CCR_FS_SM          = 0,  // Sm mode I2C
    I2C_CCR_FS_FM          = 1   // Fm mode I2C
} I2C_CCR_FS_t;

// Bit 14: DUTY
typedef enum {
    I2C_CCR_DUTY_2         = 0,  // Fm mode tlow/thigh = 2
    I2C_CCR_DUTY_16_9      = 1   // Fm mode tlow/thigh = 16/9
} I2C_CCR_DUTY_t;

// --- I2C_TRISE (TRISE Register) ---
// Không cần enum cho TRISE[5:0] vì đây là giá trị số (0-63), dùng trực tiếp


typedef enum {
    I2C_SCL_10KHZ  = 10000, // 10 kHz
    I2C_SCL_20KHZ  = 20000, // 20 kHz
    I2C_SCL_50KHZ  = 50000, // 50 kHz
    I2C_SCL_100KHZ = 100000 // 100 kHz
}SCL_Freq_SM_t;


typedef enum {
    I2C_MODE_TRANSMIT = 0, // Transmit mode
    I2C_MODE_RECEIVE  = 1  // Receive mode
}Mode_communication_t;

typedef struct 
{
    I2C_CR1_SWRST_t SWRST; // Software reset
    I2C_CR1_ALERT_t ALERT; // SMBus alert
    I2C_CR1_PEC_t PEC; // Packet error checking
    I2C_CR1_POS_t POS; // Acknowledge/PEC position
    I2C_CR1_ACK_t ACK; // Acknowledge enable
    I2C_CR1_STOP_t STOP; // Stop generation
    I2C_CR1_START_t START; // Start generation
    I2C_CR1_NOSTRETCH_t NOSTRETCH; // Clock stretching disable
    I2C_CR1_ENGC_t ENGC; // General call enable
    I2C_CR1_ENPEC_t ENPEC; // Packet error checking enable
    I2C_CR1_ENARP_t ENARP; // ARP enable
    I2C_CR1_SMBTYPE_t SMBTYPE; // SMBus type
    I2C_CR1_SMBUS_t SMBUS; // SMBus mode
    I2C_CR1_PE_t PE; // Peripheral enable
    I2C_CR2_LAST_t LAST; // Last DMA transfer
    I2C_CR2_DMAEN_t DMAEN; // DMA enable
    I2C_CR2_ITBUFEN_t ITBUFEN; // Buffer interrupt enable
    I2C_CR2_ITEVTEN_t ITEVTEN; // Event interrupt enable
    I2C_CR2_ITERREN_t ITERREN; // Error interrupt enable
    I2C_CR2_FREQ_t FREQ; // Peripheral clock frequency
    I2C_OAR1_ADDMODE_t ADDMODE; // Addressing mode
    I2C_OAR2_ENDUAL_t ENDUAL; // Dual addressing mode enable
    I2C_SR1_SMBALERT_t SMBALERT; // SMBus alert
    I2C_SR1_TIMEOUT_t TIMEOUT; // Timeout or Tlow error
    I2C_SR1_PECERR_t PECERR; // Packet error checking error
    I2C_SR1_OVR_t OVR; // Overrun or underrun error
    I2C_SR1_AF_t AF; // Acknowledge failure
    I2C_SR1_ARLO_t ARLO; // Arbitration lost error
    I2C_SR1_BERR_t BERR; // Bus error
    I2C_SR1_TXE_t TXE; // Data register empty
    I2C_SR1_RXNE_t RXNE; // Data register not empty
    I2C_SR1_STOPF_t STOPF; // Stop detection flag
    I2C_SR1_ADD10_t ADD10; // 10-bit header sent
    I2C_SR1_BTF_t BTF; // Byte transfer finished
    I2C_SR1_ADDR_t ADDR; // Address matched
    I2C_SR1_SB_t SB; // Start bit
    I2C_SR2_DUALF_t DUALF; // Dual flag
    I2C_SR2_SMBHOST_t SMBHOST; // SMBus host header
    I2C_SR2_SMBDEFAULT_t SMBDEFAULT; // SMBus device default address
    I2C_SR2_GENCALL_t GENCALL; // General call address
    I2C_SR2_TRA_t TRA; // Transmitter/Receiver mode
    I2C_SR2_BUSY_t BUSY; // Bus busy
    I2C_SR2_MSL_t MSL; // Master/Slave mode
    I2C_CCR_FS_t FS; // Fast/Standard mode
    I2C_CCR_DUTY_t DUTY; // Fast mode duty cycle
    uint8_t TRISE; // Rise time
    uint8_t SR1; // Status register 1
    uint8_t SR2; // Status register 2
    uint8_t DR; // Data register
    uint8_t OAR2; // Own address register 2
    uint8_t OAR1; // Own address register 1
    uint8_t CR2; // Control register 2
    uint8_t CR1; // Control register 1
    SCL_Freq_SM_t Freq_SCL_SM;
    I2C_Type_t I2C_Type; // I2C type (I2C1 or I2C2)
    Pin_gpio_t SCL_Pin; // SCL pin configuration
    Pin_gpio_t SDA_Pin; // SDA pin configuration
    Port_t SCL_Port; // SCL port configuration
    Port_t SDA_Port; // SDA port configuration


}Custom_I2C_t;

void InitI2C(Custom_I2C_t *i2c_config);


#endif // I2C_HANDMADE_H











