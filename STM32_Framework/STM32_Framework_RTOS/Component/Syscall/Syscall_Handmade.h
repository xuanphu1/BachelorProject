#ifndef  __SYSCALL_HANDMADE_H__
#define __SYSCALL_HANDMADE_H__
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include "stdint.h"

#define __set_MSP(addr)  __asm__ volatile ("MSR msp, %0" :: "r" (addr) : )

void *_sbrk(ptrdiff_t incr);

/* Lấy dung lượng còn lại của Flash */
uint32_t get_free_flash(void);

/* Lấy dung lượng còn lại của RAM */
uint32_t get_free_ram(void);

/* Lấy dung lượng còn lại của Heap */
uint32_t get_free_heap(void);

/* Lấy dung lượng còn lại của Stack */
uint32_t get_free_stack(void);

uint32_t get_flash_used_percentage();
uint32_t get_ram_used_percentage();

uint32_t get_heap_used_percentage();
uint32_t get_stack_used_percentage();
#endif // __SYSCALL_HANDMADE_H__