#include "MutexRTOS.h"


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
