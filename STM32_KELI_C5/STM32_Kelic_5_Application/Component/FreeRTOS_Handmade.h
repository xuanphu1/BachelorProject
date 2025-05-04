#ifndef _FREE_RTOS_HANDMADE_
#define _FREE_RTOS_HANDMADE_
#include "stdint.h"
#include "cortex_m3.h"
#include "SCB_Base.h"
#include "Systick_Handmade.h"
#include "stdlib.h"




#define SIZE_EACH_STACK 128
#define NUMBER_TASK	9

typedef enum {
	TASK_FREE = 0,
	TASK_RUNNING,
	TASK_SLEEP,
	TASK_PAUSE
	
}StatusTask_t;


typedef enum {
	
	TASK_IDLE,
	TASK_NULL = NUMBER_TASK + 1
}Task_t;

typedef struct 
{
    StatusTask_t StatusTask;
    void (*MainFunction)();
    CPU_TypeDef CPU;
    uint32_t Stack[SIZE_EACH_STACK]; // 1KB
    uint32_t SleepUntil; // Th?i di?m dánh th?c (tính b?ng ms)
		uint32_t SleepStart;    // Th?i di?m b?t d?u ng?
    uint32_t SleepDuration; // Th?i gian ng? (ms)
		uint8_t Priority;         // Ð? uu tiên: 0 (th?p nh?t) - 255 (cao nh?t)
} Task_TypeDef_t;

extern Task_TypeDef_t Task[NUMBER_TASK];


typedef struct {
	uint8_t CurrentTaskID;
	uint8_t Total;
	uint8_t Running;

}TaskManager_t;

extern TaskManager_t TaskManager;




// --- Queue ---
typedef struct {
    uint32_t* Buffer;        // M?ng luu d? li?u
    uint16_t Size;           // Kích thu?c queue
    uint16_t Front;          // Ch? s? d?u
    uint16_t Rear;           // Ch? s? cu?i
    uint16_t Count;          // S? ph?n t? hi?n t?i
} Queue_t;

// --- Mutex ---
typedef struct {
    uint8_t Locked;          // 0: t? do, 1: b? khóa
    uint8_t Owner;            // Task s? h?u mutex
} Mutex_t;



void Task_Begin(void);
uint32_t Task_Create(void (*MainFunction)(), uint8_t priority);
void Task_End(void);
void Task_Delete(void (*MainFunction)());
void Task_Delay(uint32_t TimeMs);
void RTOS_Run(void);


Queue_t* Queue_Create(uint16_t size);
uint32_t Queue_Send(Queue_t* queue, uint32_t data);
uint32_t Queue_Receive(Queue_t* queue, uint32_t* data);
uint32_t Queue_Send_FromISR(Queue_t* queue, uint8_t data);

Mutex_t* Mutex_Create(void);
uint32_t Mutex_Lock(Mutex_t* mutex);
uint32_t Mutex_Unlock(Mutex_t* mutex);

#endif






