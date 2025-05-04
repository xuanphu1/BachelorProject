#include "Syscall_Handmade.h"

extern uint32_t _sheap;    // Bắt đầu Heap (từ linker script)
extern uint32_t _eheap;    // Kết thúc Heap
extern uint32_t _estack;   // Đỉnh Stack (cuối RAM)
extern uint32_t _sstack;   // Cuối Stack (thấp nhất)
extern uint32_t _etext;    // Kết thúc vùng .text (code)
extern uint32_t _ebss;     // Kết thúc vùng .bss (biến chưa khởi tạo)
extern uint32_t _edata;    // Kết thúc vùng .data (biến đã khởi tạo)

static volatile uint32_t *heap_end = &_sheap;  // Con trỏ theo dõi cuối Heap

void *_sbrk(ptrdiff_t incr) {
    volatile uint32_t *prev_heap_end = (uint32_t *)heap_end;
    volatile uint32_t *new_heap_end = prev_heap_end + incr;

    // Kiểm tra nếu Heap tràn vào Stack
    if (new_heap_end > &_eheap) {
        errno = ENOMEM;  // Lỗi không đủ bộ nhớ
        return (void *)-1;
    }

    heap_end = new_heap_end;
    return (void *)prev_heap_end;
}

/* Lấy dung lượng còn lại của Flash */
uint32_t get_free_flash(void) {
    return (uint32_t)((uint8_t *)&_estack - (uint8_t *)&_etext);
}

/* Lấy dung lượng còn lại của RAM */
uint32_t get_free_ram(void) {
    return (uint32_t)((uint8_t *)&_estack - (uint8_t *)&_ebss);
}

/* Lấy dung lượng còn lại của Heap */
uint32_t get_free_heap(void) {
    return (uint32_t)((uint8_t *)&_eheap - (uint8_t *)heap_end);
}

/* Lấy dung lượng còn lại của Stack */
uint32_t get_free_stack(void) {
    uint8_t *sp;
    __asm volatile ("MRS %0, MSP" : "=r" (sp));  // Lấy giá trị Stack Pointer hiện tại
    return (uint32_t)(sp - (uint8_t *)&_sstack);
}

uint32_t get_flash_used_percentage() {
    return (100 * (*(uint8_t *)&_etext)) / (*(uint8_t *)&_estack);
}

uint32_t get_ram_used_percentage() {
    return (100 * ((uint8_t *)&_eheap - (uint8_t *)&_ebss)) / ((uint8_t *)&_estack - (uint8_t *)&_ebss);
}

uint32_t get_heap_used_percentage() {
    return (100 * ((uint8_t *)heap_end - (uint8_t *)&_sheap)) / ((uint8_t *)&_eheap - (uint8_t *)&_sheap);
}

uint32_t get_stack_used_percentage() {
    uint8_t *sp;
    __asm volatile ("MRS %0, MSP" : "=r" (sp));
    return (100 * ((uint8_t *)&_estack - sp)) / ((uint8_t *)&_estack - (uint8_t *)&_sstack);
}

