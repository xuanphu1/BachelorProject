#include "FreeRTOS_Handmade.h"

void* pvPortMalloc(size_t size) {
    void* ptr;
    __disable_irq(); 
    ptr = malloc(size);
    __enable_irq();  
    return ptr;
}

void vPortFree(void* ptr) {
    if (ptr != NULL) {
        __disable_irq();
        free(ptr);
        __enable_irq();
    }
}



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
	Task[TASK_IDLE].StatusTask = TASK_RUNNING;
	Task[TASK_IDLE].Priority = 0; // Uu tiên th?p nh?t cho idle task
}
	

uint32_t Task_Create(void (*MainFunction)(), uint8_t priority) {
    uint8_t idxTaskFree;
    for (idxTaskFree = 1; idxTaskFree < NUMBER_TASK ; idxTaskFree++) {
        if (Task[idxTaskFree].StatusTask == TASK_FREE) {
            Task[idxTaskFree].StatusTask = TASK_RUNNING;
            Task[idxTaskFree].MainFunction = MainFunction;
            Task[idxTaskFree].Priority = priority; // Gán d? uu tiên

            Task[idxTaskFree].Stack[SIZE_EACH_STACK - 1 ] = 0;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK	- 2 ] = 0;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK	- 3 ] = 0x21000000;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK	- 4 ] = (uint32_t)MainFunction;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK	- 5 ] = (uint32_t)Task_End;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK	- 6 ] = 0;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK	- 7 ] = 0;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK	- 8 ] = 0;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK	- 9 ] = 0;
            Task[idxTaskFree].Stack[SIZE_EACH_STACK	- 10] = 0;
            Task[idxTaskFree].CPU.SP = (uint32_t)&Task[idxTaskFree].Stack[SIZE_EACH_STACK - 10 ];
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
		for (idxFunction = 1 ; idxFunction < NUMBER_TASK ; idxFunction++){
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
    SCB_BASE_HANDMADE->SCB_ICSR |= (1 << SCB_ICSR_PENDSVSET_POS);
}




// --- Queue Implementation ---
Queue_t* Queue_Create(uint16_t size) {
    Queue_t* queue = (Queue_t*)malloc(sizeof(Queue_t));
    if (queue == NULL) return NULL;

    queue->Buffer = (uint32_t*)malloc(size * sizeof(uint32_t));
    if (queue->Buffer == NULL) {
        free(queue);
        return NULL;
    }

    queue->Size = size;
    queue->Front = 0;
    queue->Rear = 0;
    queue->Count = 0;
    return queue;
}

uint32_t Queue_Send(Queue_t* queue, uint32_t data) {
    if (queue == NULL || queue->Count >= queue->Size) {
        return 0; // Queue d?y ho?c không t?n t?i
    }
		__disable_irq();
    queue->Buffer[queue->Rear] = data;
    queue->Rear = (queue->Rear + 1) % queue->Size;
    queue->Count++;
		__enable_irq();
    return 1;
}

uint32_t Queue_Receive(Queue_t* queue, uint32_t* data) {
    if (queue == NULL || queue->Count == 0) {
        return 0; // Queue r?ng ho?c không t?n t?i
    }
		__disable_irq();
    *data = queue->Buffer[queue->Front];
    queue->Front = (queue->Front + 1) % queue->Size;
    queue->Count--;
		__enable_irq();
    return 1;
}

// --- Mutex Implementation ---
Mutex_t* Mutex_Create(void) {
    Mutex_t* mutex = (Mutex_t*)malloc(sizeof(Mutex_t));
    if (mutex == NULL) return NULL;

    mutex->Locked = 0;
    mutex->Owner = TASK_NULL;
    return mutex;
}

uint32_t Mutex_Lock(Mutex_t* mutex) {
    if (mutex == NULL) return 0;

    while (mutex->Locked) {
        if (mutex->Owner == TaskManager.CurrentTaskID) {
            return 1; // Ðã s? h?u, cho phép khóa l?i
        }
        Task_Delay(1); // Ch? n?u b? khóa b?i task khác
    }

    mutex->Locked = 1;
    mutex->Owner = TaskManager.CurrentTaskID;
    return 1;
}

uint32_t Mutex_Unlock(Mutex_t* mutex) {
    if (mutex == NULL || mutex->Owner != TaskManager.CurrentTaskID || !mutex->Locked) {
        return 0; // Không s? h?u ho?c không khóa
    }

    mutex->Locked = 0;
    mutex->Owner = TASK_NULL;
    return 1;
}

