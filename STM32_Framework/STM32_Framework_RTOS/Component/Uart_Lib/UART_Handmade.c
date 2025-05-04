#include "UART_Handmade.h"

static uint16_t USART_CalculateBRR(uint32_t PCLK, uint32_t BaudRate) {
    float USARTDIV = (float) PCLK / (16 * BaudRate);
    uint16_t mantissa = (uint16_t) USARTDIV;
    uint8_t fraction = (USARTDIV - mantissa) * 16;
    return ((mantissa << 4) | (fraction & 0x0F));
}

volatile UART_Handmade_t *UART_List[] = {USART1_HANDMADE,USART2_HANDMADE,USART3_HANDMADE};

Error_UART_t UARTInit(Custom_USART_Config_t *uartConfig){

    // Kiểm tra con trỏ NULL
    if (uartConfig == NULL) {
        return UART_NULL_PTR;
    }
    volatile UART_Handmade_t *UARTx = UART_List[uartConfig->USARTx];

    // Kiểm tra con trỏ UARTx hợp lệ
    if (UARTx == NULL) {
        return UART_ERROR;
    }

    if(UARTx == UART_1) Enable_Clock_RCC_APB2(USART1_EN_CLK);
    else Enable_Clock_RCC_APB1((uartConfig->USARTx == UART_2) ? USART2_EN_CLK : USART3_EN_CLK);
    
    // 1️⃣ Bật clock GPIO trước khi bật UART
    if (uartConfig->USARTx == UART_1) {
        Enable_Clock_RCC_APB2(USART1_EN_CLK);
        Enable_Clock_RCC_APB2(IOPA_EN_CLK);
    } else if (uartConfig->USARTx == UART_2) {
        Enable_Clock_RCC_APB1(USART2_EN_CLK);
        Enable_Clock_RCC_APB2(IOPA_EN_CLK);
    } else {
        Enable_Clock_RCC_APB1(USART3_EN_CLK);
        Enable_Clock_RCC_APB2(IOPB_EN_CLK);
    }

    // 2️⃣ Cấu hình GPIO TX và RX theo UART đã chọn
    GPIO_config_t gpio_tx, gpio_rx;
    if (uartConfig->USARTx == UART_1) {
        gpio_tx.port = Port_A; gpio_tx.pin = PIN_9;
        gpio_rx.port = Port_A; gpio_rx.pin = PIN_10;
    } else if (uartConfig->USARTx == UART_2) {
        gpio_tx.port = Port_A; gpio_tx.pin = PIN_2;
        gpio_rx.port = Port_A; gpio_rx.pin = PIN_3;
    } else {
        gpio_tx.port = Port_B; gpio_tx.pin = PIN_10;
        gpio_rx.port = Port_B; gpio_rx.pin = PIN_11;
    }

    gpio_tx.mode = OUTPUT_MODE_50_MHZ;
    gpio_tx.cnf_mode = CNF_MODE_10; // Alternate Function Push-Pull
    InitGPIO(&gpio_tx);

    gpio_rx.mode = INPUT_MODE;
    gpio_rx.cnf_mode = CNF_MODE_01; // Input Floating
    InitGPIO(&gpio_rx);


    // Xóa các thanh ghi trước khi cấu hình để tránh giá trị thừa
    UARTx->UART_CR1 = 0;
    UARTx->UART_CR2 = 0;
    UARTx->UART_CR3 = 0;
    UARTx->UART_BRR = 0;
    UARTx->UART_GTPR = 0;

    // Cấu hình thanh ghi UART_CR1
    UARTx->UART_CR1 |= (uartConfig->usartEnable << 13) |      // UE: USART enable
                       (uartConfig->wordLength << 12) |       // M: Word length
                       (uartConfig->wakeupMethod << 11) |     // WAKE: Wakeup method
                       (uartConfig->parityControl << 10) |    // PCE: Parity control enable
                       (uartConfig->paritySelection << 9) |   // PS: Parity selection
                       (uartConfig->peInterrupt << 8) |       // PEIE: Parity error interrupt
                       (uartConfig->txeInterrupt << 7) |      // TXEIE: Transmit empty interrupt
                       (uartConfig->tcInterrupt << 6) |       // TCIE: Transmission complete interrupt
                       (uartConfig->rxneInterrupt << 5) |     // RXNEIE: Receive not empty interrupt
                       (uartConfig->idleInterrupt << 4) |     // IDLEIE: IDLE line interrupt
                       (uartConfig->transmitterEnable << 3) | // TE: Transmitter enable
                       (uartConfig->receiverEnable << 2) |    // RE: Receiver enable
                       (uartConfig->receiverWakeup << 1) |    // RWU: Receiver wakeup
                       (uartConfig->sendBreak << 0);          // SBK: Send break

    // Cấu hình thanh ghi UART_CR2
    UARTx->UART_CR2 |= (uartConfig->linMode << 14) |          // LINEN: LIN mode enable
                       (uartConfig->stopBits << 12) |         // STOP: Stop bits
                       (uartConfig->clockEnable << 11) |      // CLKEN: Clock enable
                       (uartConfig->clockPolarity << 10) |    // CPOL: Clock polarity
                       (uartConfig->clockPhase << 9) |        // CPHA: Clock phase
                       (uartConfig->lastBitClock << 8) |      // LBCL: Last bit clock pulse
                       (uartConfig->linBreakInterrupt << 6) | // LBDIE: LIN break detection interrupt
                       (uartConfig->linBreakLength << 5) |    // LBDL: LIN break detection length
                       (uartConfig->nodeAddress & 0x0F);      // ADD[3:0]: Node address

    // Cấu hình thanh ghi UART_CR3
    UARTx->UART_CR3 |= (uartConfig->ctsInterrupt << 10) |     // CTSIE: CTS interrupt enable
                       (uartConfig->ctsEnable << 9) |         // CTSE: CTS enable
                       (uartConfig->rtsEnable << 8) |         // RTSE: RTS enable
                       (uartConfig->dmaTransmitter << 7) |    // DMAT: DMA enable transmitter
                       (uartConfig->dmaReceiver << 6) |       // DMAR: DMA enable receiver
                       (uartConfig->smartcardMode << 5) |     // SCEN: Smartcard mode enable
                       (uartConfig->smartcardNack << 4) |     // NACK: Smartcard NACK enable
                       (uartConfig->halfDuplex << 3) |        // HDSEL: Half-duplex selection
                       (uartConfig->irdaLowPower << 2) |      // IRLP: IrDA low-power
                       (uartConfig->irdaMode << 1) |          // IREN: IrDA mode enable
                       (uartConfig->errorInterrupt << 0);     // EIE: Error interrupt enable

    // Cấu hình thanh ghi UART_BRR (Baud rate)
    UARTx->UART_BRR = USART_CalculateBRR(   (uartConfig->USARTx == UART_1 ? (uint32_t)getFrequencyAPB2() : (uint32_t)getFrequencyAPB1()),
                                            uartConfig->baudUART);

    // Cấu hình thanh ghi UART_GTPR (Guard time and prescaler)
    UARTx->UART_GTPR = (uartConfig->guardTime << 8) |         // GT[7:0]: Guard time
                       (uartConfig->prescalerValue & 0xFF);   // PSC[7:0]: Prescaler value

    // Kiểm tra trạng thái ban đầu (tùy chọn)
    if (UARTx->UART_SR & (1 << 3)) { // Ví dụ: Kiểm tra ORE (Overrun error)
        return UART_ERROR; // Báo lỗi nếu có overrun ngay sau khi khởi tạo
    }
    UARTx->UART_CR1 |= (1 << 3); // Bật bộ truyền (TE)
    UARTx->UART_CR1 |= (1 << 2); // Bật bộ nhận (RE)
    return UART_OK; // Trả về thành công
    

}
Error_UART_t TransmitDataUART(UART_Type_t uartx, uint8_t *Data, uint8_t lengthData) {
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    if (UARTx == NULL || Data == NULL) {
        return UART_ERROR;
    }

    // Kiểm tra UART có sẵn sàng để gửi không (TE phải bật)
    if (!(UARTx->UART_CR1 & (1 << 3))) {  
        return UART_NOT_READY; // UART chưa sẵn sàng để truyền
    }

    // Gửi dữ liệu qua UART
    for (uint8_t idx = 0; idx < lengthData; idx++) {
        while (!(UARTx->UART_SR & (1 << 7))); // Chờ TXE = 1 (Data Register Empty)
        UARTx->UART_DR = Data[idx]; // Gửi dữ liệu
    }

    // Chờ cho đến khi truyền xong toàn bộ dữ liệu (TC = 1)
    while (!(UARTx->UART_SR & (1 << 6))); 

    return UART_OK;
}

Error_UART_t ReceiveDataUART(UART_Type_t uartx, uint8_t *Data, uint8_t lengthData) {
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    if (UARTx == NULL || Data == NULL) {
        return UART_ERROR;
    }

    // Kiểm tra xem có dữ liệu trong UART không (RXNE = 1)
    if (!(UARTx->UART_SR & (1 << 5))) {  
        return UART_NO_DATA; // Không có dữ liệu
    }

    // Đọc dữ liệu khi có dữ liệu sẵn sàng
    for (uint8_t idx = 0; idx < lengthData; idx++) {
        while (!(UARTx->UART_SR & (1 << 5))); // Chờ RXNE = 1 (Data Received)
        Data[idx] = UARTx->UART_DR; // Lưu dữ liệu nhận được

        // Kiểm tra nếu không còn dữ liệu nữa thì thoát
        if (!(UARTx->UART_SR & (1 << 5))) {
            break;
        }
    }

    return UART_OK;
}


Error_UART_t EnableInterrupt_RX_UARTx(UART_Type_t uartx) {
    if (uartx < UART_1 || uartx > UART_3) return UART_ERROR; // Kiểm tra hợp lệ
    
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    if (UARTx == NULL) return UART_ERROR; // Kiểm tra con trỏ null
    
    Enable_Intterupt_NVIC((Custom_IRQn)(uartx + Custom_USART1_IRQn)); // Bật NVIC
    
    UARTx->UART_CR1 |= (1 << 5); // Bật ngắt RXNE (Nhận dữ liệu)
    
    return UART_OK; // Trả về thành công
}
void interruptEnable(UART_Type_t uartx){
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    UARTx->UART_CR1 |= (1 << 5); // T?t RXNEIE
}

void interruptDisable(UART_Type_t uartx){
    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    UARTx->UART_CR1 &= ~(1 << 5);
}


Error_UART_t ReceiveDataUART_IT(UART_Type_t uartx, uint8_t *Buffer_output, uint8_t length) {
    if (uartx < UART_1 || uartx > UART_3 || Buffer_output == NULL || length == 0) {
        return UART_ERROR;
    }

    volatile UART_Handmade_t *UARTx = UART_List[uartx];
    static volatile uint8_t idx = 0; // Biến giữ trạng thái

    // Kiểm tra nếu có dữ liệu đến (RXNE = 1)
    if (UARTx->UART_SR & (1 << 5)) {
        uint8_t Data = UARTx->UART_DR; // Đọc dữ liệu từ UART (dạng số HEX)

        if (idx < length) { // Chưa nhận đủ dữ liệu
            Buffer_output[idx++] = Data;
        }   // Khi nhận đủ dữ liệu
        if (idx >= length){
            idx = 0; // Reset index để nhận dữ liệu mới
            return UART_OK;
        }       
        
    }
    return UART_NO_DATA;
}

