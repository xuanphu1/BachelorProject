#ifndef _FREE_RTOS_HANDMADE_
#define _FREE_RTOS_HANDMADE_
#include "stdint.h"
#include "cortex_m3.h"
#include "SCB_Base.h"
#include "Systick_Handmade.h"

typedef enum {
	TASK_FREE = 0,
	TASK_RUNNING,
	TASK_SLEEP,
	TASK_PAUSE
	
}StatusTask_t;


typedef enum {
	
	TASK_IDLE,
	TASK_1,
	TASK_2,
	TASK_3,
	TASK_4,
	TASK_5,
	TASK_6,
	TASK_7,
	TASK_8,
	TASK_NULL
	

}Task_t;

typedef struct 
{
    StatusTask_t StatusTask;
    void (*MainFunction)();
    CPU_TypeDef CPU;
    unsigned long Stack[256]; // 1KB
    uint32_t SleepUntil; // Th?i di?m dánh th?c (tính b?ng ms)
		uint32_t SleepStart;    // Th?i di?m b?t d?u ng?
    uint32_t SleepDuration; // Th?i gian ng? (ms)
		uint8_t Priority;         // Ð? uu tiên: 0 (th?p nh?t) - 255 (cao nh?t)
} Task_TypeDef_t;

extern Task_TypeDef_t Task[9];


typedef struct {
	Task_t CurrentTaskID;
	uint8_t Total;
	uint8_t Running;

}TaskManager_t;

extern TaskManager_t TaskManager;

void Task_Begin(void);
uint32_t Task_Create(void (*MainFunction)(), uint8_t priority);
void Task_End(void);
void Task_Delete(void (*MainFunction)());
void Task_Delay(uint32_t TimeMs);
void RTOS_Run(void);

#endif


