/* Chỉ định điểm bắt đầu chương trình */
ENTRY(Reset_Handler)

/* Định nghĩa kích thước Heap và Stack */
_heap_size = 2048;   /* 2KB Heap */
_stack_size = 2048;  /* 2KB Stack */

/* Định nghĩa bộ nhớ */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 32K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    /* Bảng vector ngắt - Đặt ở đầu Flash */
    .isr_vector :
    {
        KEEP(*(.isr_vector))   /* Giữ bảng vector */
    } > FLASH

    /* Code chương trình */
    .text :
    {
        *(.text*)       /* Mã lệnh chương trình */
        *(.rodata*)     /* Dữ liệu chỉ đọc */
        . = ALIGN(4);
        _etext = .;     /* Đánh dấu cuối vùng code */
    } > FLASH

    /* Lưu địa chỉ dữ liệu khởi tạo trong Flash */
    _la_data = LOADADDR(.data);

    /* Vùng dữ liệu đã khởi tạo trong RAM */
    .data :
    {
        _sdata = .;    /* Bắt đầu dữ liệu đã khởi tạo */
        *(.data*)
        . = ALIGN(4);
        _edata = .;    /* Kết thúc dữ liệu đã khởi tạo */
    } > RAM AT> FLASH

    /* Biến chưa khởi tạo (bss) */
    .bss :
    {
        _sbss = .;     /* Bắt đầu biến chưa khởi tạo */
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;     /* Kết thúc biến chưa khởi tạo */
    } > RAM

    /* Heap - Dùng cho malloc() */
    .heap (NOLOAD) :
    {
        . = ALIGN(8);
        _sheap = .;    /* Bắt đầu Heap */
        . += _heap_size;
        _eheap = .;    /* Kết thúc Heap */
    } > RAM

    /* Stack - Đặt ở cuối RAM */
    .stack (NOLOAD) :
    {
        _estack = ORIGIN(RAM) + LENGTH(RAM);  /* Đặt _estack tại cuối RAM */
        _sstack = _estack - _stack_size;      /* Đặt _sstack tại vị trí thấp nhất của Stack */
    } > RAM
}
