#include "NVIC_Handmade.h"


void Enable_Intterupt_NVIC(Custom_IRQn IRQ) {
    NVIC_HANDMADE->ISER[IRQ / 32] |= (1 << (IRQ % 32)); // Bật ngắt đúng nhóm
}

void Disable_Intterupt_NVIC(Custom_IRQn IRQ) {
    NVIC_HANDMADE->ICER[IRQ / 32] |= (1 << (IRQ % 32)); // Tắt ngắt đúng nhóm
}

void setPriorityInterrupt(Custom_IRQn IRQ, uint8_t Priority) {
    uint8_t IPRx = IRQ / 4;         // Tìm thanh ghi IPR tương ứng
    uint8_t offset_IPRx = IRQ % 4;  // Vị trí trong thanh ghi (0-3)

    NVIC_HANDMADE->IPR[IPRx] &= ~(0xFF << (offset_IPRx * 8));  // Xóa giá trị cũ
    NVIC_HANDMADE->IPR[IPRx] |= (Priority << (offset_IPRx * 8 + 4)); // Gán mức ưu tiên mới
}