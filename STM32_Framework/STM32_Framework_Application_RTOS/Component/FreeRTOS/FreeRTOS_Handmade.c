#include "FreeRTOS_Handmade.h"

uint32_t isIdle_Task = 1;

Task_TypeDef_t Task[9];
TaskManager_t TaskManager;

void Task_End(void){
	
	if(TaskManager.CurrentTaskID != 0){
		Task[TaskManager.CurrentTaskID].StatusTask = TASK_FREE;
		TriggerSV_Call_Interrupt();
	}
}

void Task_Idle(void) {
	while (1) {
		__asm("NOP");
		Task_Delay(1);
	}
}

// T?o t�c v? m?i v?i PSP
uint32_t Task_Create(void (*MainFunction)(), uint8_t priority) {

    for (uint8_t idxTaskFree = 1; idxTaskFree < NUMBER_TASK; idxTaskFree++) {
        if (Task[idxTaskFree].StatusTask == TASK_FREE) {
            Task[idxTaskFree].StatusTask = TASK_RUNNING;
            Task[idxTaskFree].MainFunction = MainFunction;
            Task[idxTaskFree].Priority = priority; // G�n d? uu ti�n

            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 1 ] = 0;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 2 ] = 0;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 3 ] = 0x01000000;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 4 ] = (uint32_t)MainFunction;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 5 ] = (uint32_t)Task_End;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 6 ] = 0; // R12
            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 7 ] = 0; // R3
            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 8 ] = 0; // R2
            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 9 ] = 0; // R1
            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 10] = 0; // R0
						
            Task[idxTaskFree].CPU.SP = (uint32_t)&Task[idxTaskFree].Stack[SIZE_EACH_STACK - 10 ];
            TaskManager.Running++;
            return 1;
        }
    }
    return 0;
}

// C?p nh?t h�m Task_Begin d? chuy?n sang ch? d? PSP cho task Idle
void Task_Begin(void) {
		
    TaskManager.CurrentTaskID = TASK_IDLE;
    TaskManager.Running = 1;
    TaskManager.Total = 1;
    Task[TASK_IDLE].StatusTask = TASK_RUNNING;
    Task[TASK_IDLE].Priority = 0; // Uu ti�n th?p nh?t cho idle task

    // Kh?i t?o stack cho task idle
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 1 ] = 0;
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 2 ] = 0;
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 3 ] = 0x01000000;
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 4 ] = (uint32_t)Task_Idle;
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 5 ] = (uint32_t)Task_End;
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 6 ] = 0;  // R12
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 7 ] = 0;  // R3
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 8 ] = 0;  // R2
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 9 ] = 0;  // R1
    Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 10] = 0;  // R0
    Task[TASK_IDLE].CPU.SP = (uint32_t)&Task[TASK_IDLE].Stack[SIZE_EACH_STACK - 10 ];

    // Chuy?n sang PSP cho task idle
    TaskManager.Running++;
}
void Task_Delete(void (*MainFunction)()){
	
	extern int main();
	uint8_t idxFunction;
	if (MainFunction != (void*)main){
		for (idxFunction = 1 ; idxFunction < NUMBER_TASK ; idxFunction++){
			if(Task[idxFunction].MainFunction == MainFunction && Task[idxFunction].StatusTask != TASK_FREE){
				Task[idxFunction].StatusTask = TASK_FREE;
				if (TaskManager.CurrentTaskID == idxFunction) TriggerSV_Call_Interrupt();
			}
		}
	} 
}

CPU_TypeDef* Task_GetCurrentCPU(){

	return &Task[TaskManager.CurrentTaskID].CPU;
}



CPU_TypeDef* Task_GetNextCPU() {
    uint8_t highest_priority = 0;
    uint8_t Highest_Task = TASK_NULL;
    uint8_t NextTask;

    for (NextTask = 1; NextTask < NUMBER_TASK; NextTask++) {
        if (Task[NextTask].StatusTask == TASK_RUNNING || 
           (Task[NextTask].StatusTask == TASK_SLEEP && 
            (SysTick_ms - Task[NextTask].SleepStart) >= Task[NextTask].SleepDuration)) {
            if (Task[NextTask].StatusTask == TASK_SLEEP) {
                Task[NextTask].StatusTask = TASK_RUNNING;
            }
            if (Task[NextTask].Priority >= highest_priority) {
                highest_priority = Task[NextTask].Priority;
                Highest_Task = NextTask;
            }
        }
    }

    if (Highest_Task != TASK_NULL) {
        TaskManager.CurrentTaskID = Highest_Task;
        return &Task[Highest_Task].CPU;
    }

    TaskManager.CurrentTaskID = TASK_IDLE;
    return &Task[TASK_IDLE].CPU;
}


void Task_Delay(uint32_t TimeMs) {
    if (Task[TaskManager.CurrentTaskID].StatusTask != TASK_SLEEP) {
        Task[TaskManager.CurrentTaskID].StatusTask = TASK_SLEEP;
        Task[TaskManager.CurrentTaskID].SleepStart = SysTick_ms;       // Luu th?i di?m b?t d?u
        Task[TaskManager.CurrentTaskID].SleepDuration = TimeMs; // Luu th?i gian ng?
    }
    TriggerSV_Call_Interrupt();
}

