#ifndef _MUTEX_RTOS_H
#define _MUTEX_RTOS_H
#include "stdio.h"
#include "stdint.h"
#include "SCB_Base.h"
#include "FreeRTOS_Handmade.h"

// --- Mutex ---
typedef struct {
    uint8_t Locked;          // 0: t? do, 1: b? khóa
    uint8_t Owner;            // Task s? h?u mutex
} Mutex_t;



Mutex_t* Mutex_Create(void);
uint32_t Mutex_Lock(Mutex_t* mutex);
uint32_t Mutex_Unlock(Mutex_t* mutex);

#endif // _MUTEX_RTOS_H
