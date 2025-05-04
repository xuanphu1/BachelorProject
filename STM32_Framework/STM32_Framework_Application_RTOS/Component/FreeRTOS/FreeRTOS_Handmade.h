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
	
	TASK_IDLE = 0,
	TASK_NULL = NUMBER_TASK + 1
}Task_t;

typedef struct 
{
		CPU_TypeDef CPU;
    StatusTask_t StatusTask;
    void (*MainFunction)();
    uint32_t Stack[SIZE_EACH_STACK]; // 1KB
    uint32_t SleepUntil; // Th?i di?m d�nh th?c (t�nh b?ng ms)
		uint32_t SleepStart;    // Th?i di?m b?t d?u ng?
    uint32_t SleepDuration; // Th?i gian ng? (ms)
		uint8_t Priority;         // �? uu ti�n: 0 (th?p nh?t) - 255 (cao nh?t)
} Task_TypeDef_t;

extern Task_TypeDef_t Task[NUMBER_TASK];


typedef struct {
	uint8_t CurrentTaskID;
	uint8_t Total;
	uint8_t Running;

}TaskManager_t;

extern TaskManager_t TaskManager;







void Task_Begin(void);
uint32_t Task_Create(void (*MainFunction)(), uint8_t priority);
void Task_End(void);
void Task_Delete(void (*MainFunction)());
void Task_Delay(uint32_t TimeMs);




#endif






