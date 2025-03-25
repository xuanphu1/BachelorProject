#include "DMA_Handmade.h"

/**
 * @brief Khởi tạo cấu hình cho một kênh DMA
 * @param dmaConfig: Con trỏ tới cấu hình DMA
 * @return DMA_Error_t: Trạng thái thực thi
 */
DMA_Error_t DMA_Init(DMA_Config_t *dmaConfig){
    // Kiểm tra tham số đầu vào
    if (dmaConfig == NULL || 
        dmaConfig->Channel > DMA_CHANNEL_7 ||
        dmaConfig->Priority > DMA_VERY_HIGH_PRIORITY ||
        dmaConfig->PeripheralIncrement > ENABLE_DMA_PINC ||
        dmaConfig->MemoryIncrement > ENABLE_DMA_MINC ||
        dmaConfig->PeripheralSize > DMA_PSIZE_32BIT ||
        dmaConfig->MemorySize > DMA_MSIZE_32BIT ||
        dmaConfig->CircularMode > DMA_CIRC_ENABLE ||
        dmaConfig->Direction > DMA_DIR_MEM_TO_PERIPH ||
        dmaConfig->TransferErrorInt > DMA_TEIE_ENABLE ||
        dmaConfig->HalfTransferInt > DMA_HTIE_ENABLE ||
        dmaConfig->TransferCompleteInt > DMA_TCIE_ENABLE ||
        dmaConfig->NumData == 0 ||
        dmaConfig->PeripheralAddress == 0 ||
        dmaConfig->MemoryAddress == 0) {
        return DMA_ERROR_INVALID_PARAM;
    }

    // Bật clock cho DMA1
    Enable_Clock_RCC_AHB(DMA1_EN_CLK);

    // Vô hiệu hóa kênh DMA trước khi cấu hình
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR &= ~(1 << 0); // Disable DMA

    
    // Cấu hình kênh DMA
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->Priority << 12);         // Độ ưu tiên
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->PeripheralIncrement << 6); // Tăng địa chỉ ngoại vi
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->MemoryIncrement << 7);     // Tăng địa chỉ bộ nhớ
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->PeripheralSize << 8);      // Kích thước ngoại vi
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->MemorySize << 10);         // Kích thước bộ nhớ
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->CircularMode << 5);        // Chế độ vòng lặp
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->Direction << 4);           // Hướng truyền
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->TransferErrorInt << 3);    // Ngắt lỗi truyền
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->HalfTransferInt << 2);     // Ngắt nửa truyền
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CCR |= (dmaConfig->TransferCompleteInt << 1); // Ngắt hoàn tất truyền

    // Cấu hình số lượng dữ liệu và địa chỉ
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CNDTR = dmaConfig->NumData;
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CPAR = dmaConfig->PeripheralAddress;
    DMA1_HANDMADE->CHANNEL[dmaConfig->Channel].DMA_CMAR = dmaConfig->MemoryAddress;

    return DMA_OK;


}
/**
 * @brief Khởi động một kênh DMA đã được cấu hình
 * @param channel: Kênh DMA cần khởi động (DMA_CHANNEL_1 đến DMA_CHANNEL_7)
 * @return DMA_Error_t: Trạng thái thực thi
 */
DMA_Error_t DMA_Start(DMAChannel_t channel) {
    // Kiểm tra kênh hợp lệ
    if (channel > DMA_CHANNEL_7) {
        return DMA_ERROR_INVALID_PARAM;
    }

    // Kiểm tra xem kênh đã được cấu hình chưa (ít nhất NumData phải khác 0)
    if (DMA1_HANDMADE->CHANNEL[channel].DMA_CNDTR == 0) {
        return DMA_ERROR_NOT_INITIALIZED;
    }

    // Xóa các cờ ngắt trước khi khởi động
    DMA1_HANDMADE->DMA_IFCR |= (0xF << (channel * 4)); // Xóa cờ TCIF, HTIF, TEIF, GIF

    // Bật kênh DMA
    DMA1_HANDMADE->CHANNEL[channel].DMA_CCR |= (1 << 0);

    return DMA_OK;
}


DMA_Error_t AddressPeripheral(DMAChannel_t channel,uint32_t address_start){
    DMA1_HANDMADE->CHANNEL[channel].DMA_CPAR = address_start;
		return DMA_OK;
}
DMA_Error_t AddressMemory(DMAChannel_t channel,uint32_t address_start){
    DMA1_HANDMADE->CHANNEL[channel].DMA_CMAR = address_start;
		return DMA_OK;
}
