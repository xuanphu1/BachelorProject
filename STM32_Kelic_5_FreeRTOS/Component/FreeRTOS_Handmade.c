#include "FreeRTOS_Handmade.h"



Task_TypeDef_t Task[9];
TaskManager_t TaskManager;

void Task_End(void){
	
	if(TaskManager.CurrentTaskID != 0){
		Task[TaskManager.CurrentTaskID].StatusTask = TASK_FREE;
		SCB_BASE_HANDMADE->SCB_ICSR |= (1 << SCB_ICSR_PENDSVSET_POS);
	}
}

void RTOS_Run(void) {
	while (1) {
		__asm("NOP"); 
	}
}

void Task_Begin(void){
	
	TaskManager.CurrentTaskID = TASK_IDLE;
	TaskManager.Running = 1;
	TaskManager.Total = 1;
	Task[0].StatusTask = TASK_RUNNING;
	Task[0].Priority = 0; // Uu tiên th?p nh?t cho idle task
}
	

uint32_t Task_Create(void (*MainFunction)(), uint8_t priority) {
    Task_t idxTaskFree;
    for (idxTaskFree = TASK_1; idxTaskFree <= TASK_8; idxTaskFree++) {
        if (Task[idxTaskFree].StatusTask == TASK_FREE) {
            Task[idxTaskFree].StatusTask = TASK_RUNNING;
            Task[idxTaskFree].MainFunction = MainFunction;
            Task[idxTaskFree].Priority = priority; // Gán d? uu tiên

            Task[idxTaskFree].Stack[255] = 0;
            Task[idxTaskFree].Stack[254] = 0;
            Task[idxTaskFree].Stack[253] = 0x21000000;
            Task[idxTaskFree].Stack[252] = (uint32_t)MainFunction;
            Task[idxTaskFree].Stack[251] = (uint32_t)Task_End;
            Task[idxTaskFree].Stack[250] = 0;
            Task[idxTaskFree].Stack[249] = 0;
            Task[idxTaskFree].Stack[248] = 0;
            Task[idxTaskFree].Stack[247] = 0;
            Task[idxTaskFree].Stack[246] = 0;
            Task[idxTaskFree].CPU.SP = (uint32_t)&Task[idxTaskFree].Stack[246];
            TaskManager.Running++;
            return 1;
        }
    }
    return 0;
}

void Task_Delete(void (*MainFunction)()){
	
	extern int main();
	uint8_t idxFunction;
	if (MainFunction != (void*)main){
		for (idxFunction = TASK_1 ; idxFunction <= TASK_8 ; idxFunction++){
			if(Task[idxFunction].MainFunction == MainFunction && Task[idxFunction].StatusTask != TASK_FREE){
				Task[idxFunction].StatusTask = TASK_FREE;
				if (TaskManager.CurrentTaskID == idxFunction) SCB_BASE_HANDMADE->SCB_ICSR |= (1 << SCB_ICSR_PENDSVSET_POS);
			}
		}
	} 
}

CPU_TypeDef* Task_GetCurrentCPU(){

	return &Task[TaskManager.CurrentTaskID].CPU;
}



CPU_TypeDef* Task_GetNextCPU() {
    uint8_t highest_priority = 0;
    Task_t Highest_Task = TASK_NULL;
    Task_t NextTask;

    for (NextTask = TASK_1; NextTask <= TASK_8; NextTask++) {
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
    SCB_BASE_HANDMADE->SCB_ICSR |= (1 << SCB_ICSR_PENDSVSET_POS);
}


