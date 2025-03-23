/* Chỉ định điểm bắt đầu chương trình */
ENTRY(Reset_Handler)

/* Định nghĩa kích thước Heap và Stack */
_heap_size = 2048;   /* 2KB Heap */
_stack_size = 2048;  /* 2KB Stack */

/* Định nghĩa bộ nhớ */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    /* Bảng vector ngắt - đặt ở đầu FLASH */
    .isr_vector :
    {
        _sisr = .;                         /* VMA của bảng vector */
        KEEP(*(.isr_vector))                /* Giữ bảng vector */
        _eisr = .;
    } > FLASH

    /* Lấy địa chỉ tải (LMA) của bảng vector từ FLASH */
    _la_isr = LOADADDR(.isr_vector);

    /* Code chương trình nằm trong FLASH */
    .text :
    {
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    /* Địa chỉ tải của dữ liệu khởi tạo nằm trong FLASH */
    _la_data = LOADADDR(.data);

    /* Vùng dữ liệu đã khởi tạo trong RAM, bao gồm section .user_data */
    .data :
    {
        _sdata = .;
        *(.user_data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT> FLASH

    /* Biến chưa khởi tạo (bss) */
    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > RAM

    /* Heap - cho malloc() */
    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        _sheap = .;
        . += _heap_size;
        _eheap = .;
    } > RAM

    /* Stack - đặt ở cuối RAM */
    .stack (NOLOAD) :
    {
        _estack = ORIGIN(RAM) + LENGTH(RAM);
        _sstack = _estack - _stack_size;
    } > RAM
}
