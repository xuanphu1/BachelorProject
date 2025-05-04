#include "I2C_Handmade.h"


I2C_Handmade_t *I2C_LIST[] = {I2C1_HANDMADE, I2C2_HANDMADE};




void InitI2C(Custom_I2C_t *i2c_config){

    if(i2c_config == NULL || i2c_config->I2C_Type > I2C2 || i2c_config->SCL_Pin > PIN_15 || i2c_config->SDA_Pin > PIN_15){
        return;
    }
    Enable_Clock_RCC_APB1(i2c_config->I2C_Type + I2C1_EN_CLK); // Enable clock for I2C peripheral

    GPIO_config_t scl_config;
    GPIO_config_t sda_config;

    scl_config.port = Port_B;
    scl_config.pin = (i2c_config->I2C_Type == I2C1) ? PIN_6 : PIN_10; // SCL pin for I2C1 or I2C2
    scl_config.mode = OUTPUT_MODE_50_MHZ;
    scl_config.cnf_mode = CNF_MODE_11;

    sda_config.port = Port_B;
    sda_config.pin = (i2c_config->I2C_Type == I2C1) ? PIN_7 : PIN_11; // SDA pin for I2C1 or I2C2
    sda_config.mode = OUTPUT_MODE_50_MHZ;
    sda_config.cnf_mode = CNF_MODE_11;
    
    
    InitGPIO(&scl_config); // Initialize SCL pin
    InitGPIO(&sda_config); // Initialize SDA pin

    // Configure I2C peripheral
    I2C_Handmade_t *I2Cx = I2C_LIST[i2c_config->I2C_Type];
    I2Cx->CCR |= (i2c_config->FS << 15); // Set fast mode or standard mode
   

    I2Cx->CR2 |= (i2c_config->FREQ << 0); // Set peripheral clock frequency
    uint32_t pclk_hz = i2c_config->FREQ * 1000000; // FREQ = MHz
    uint32_t scl_hz = i2c_config->Freq_SCL_SM;
    uint16_t ccr_value = (uint16_t)(pclk_hz / (2 * scl_hz));
    I2Cx->CCR = (i2c_config->FS << 15) | ccr_value;


    I2Cx->TRISE = (1 / (1/i2c_config->FREQ)) + 1; // Set rise time register

    I2Cx->CR1 |= (1 << 0) ; // Enable I2C peripheral (PE bit in CR1 register)

}


void I2C_Command_Start(I2C_Type_t i2cx){
    if(i2cx > I2C2){
        return;
    }
    I2C_Handmade_t *I2Cx = I2C_LIST[i2cx];
    
        // Đợi bus rảnh trước khi tạo START
    while (I2Cx->SR2 & (1 << 1)); // Wait until BUSY == 0

    // Gửi lệnh START
    I2Cx->CR1 |= (1 << 8);

    // Đợi cho START thành công (SB = 1)
    while (!(I2Cx->SR1 & (1 << 0))); // Wait for SB bit
}

void I2C_Command_Address(I2C_Type_t i2cx, uint8_t address,Mode_communication_t mode){
    if(i2cx > I2C2){
        return;
    }
    I2C_Handmade_t *I2Cx = I2C_LIST[i2cx];
    (void)I2Cx->SR1; // Clear the status register 1
    I2Cx->DR = (address << 1) | mode; // Load address into data register
    while(!(I2Cx->SR1 & (1 << 1))); // Wait ADDR bit is set
    (void)I2Cx->SR1; // Clear the status register 1
    (void)I2Cx->SR2; // Clear the status register 2

}

void I2C_Transmit_byte(I2C_Type_t i2cx,uint8_t Data){
    if(i2cx > I2C2){
        return;
    }

    I2C_Handmade_t *I2Cx = I2C_LIST[i2cx];

    while (!(I2Cx->SR1 & (1 << 7))); // Wait for TXE bit to be set
    I2Cx->DR = Data; // Load data into data register

}
void I2C_Command_Stop(I2C_Type_t i2cx){
    if(i2cx > I2C2){
        return;
    }
    I2C_Handmade_t *I2Cx = I2C_LIST[i2cx];
    I2Cx->CR1 |= (1 << 9); // STOP
}


void I2C_Command_Ack(I2C_Type_t i2cx){
    if(i2cx > I2C2){
        return;
    }
    I2C_Handmade_t *I2Cx = I2C_LIST[i2cx];
    I2Cx->CR1 |= (1 << 10); // Set ACK bit in CR1 register
}
void I2C_Command_Nack(I2C_Type_t i2cx){
    if(i2cx > I2C2){
        return;
    }
    I2C_Handmade_t *I2Cx = I2C_LIST[i2cx];
    I2Cx->CR1 &= ~(1 << 10); // Clear ACK bit in CR1 register
}


