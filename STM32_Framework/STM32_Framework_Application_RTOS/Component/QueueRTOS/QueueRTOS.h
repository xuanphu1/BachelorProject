#ifndef _QUEUE_RTOS_H
#define _QUEUE_RTOS_H
#include "stdlib.h"
#include "stdint.h"
#include "SCB_Base.h"
#include "cortex_m3.h"
#include "NVIC_Handmade.h"

// --- Queue ---
typedef struct {
    uint32_t* Buffer;        // M?ng luu d? li?u
    uint16_t Size;           // Kích thu?c queue
    uint16_t Front;          // Ch? s? d?u
    uint16_t Rear;           // Ch? s? cu?i
    uint16_t Count;          // S? ph?n t? hi?n t?i
} Queue_t;


Queue_t* Queue_Create(uint8_t size);
uint32_t Queue_Send(Queue_t* queue, uint8_t data);
uint32_t Queue_Send_FromISR(Queue_t* queue, uint8_t data);
uint32_t Queue_Receive(Queue_t* queue, uint8_t* data);
uint32_t Queue_Receive_FromISR(Queue_t* queue, uint8_t* data);
uint8_t isQueueEmpty(Queue_t* queue);
uint8_t isQueueFull(Queue_t* queue);

#endif // _QUEUE_RTOS_H
