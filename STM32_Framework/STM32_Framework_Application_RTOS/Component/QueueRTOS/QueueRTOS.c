#include "QueueRTOS.h"


// --- Queue Implementation ---
Queue_t* Queue_Create(uint8_t size) {
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

uint32_t Queue_Send(Queue_t* queue, uint8_t data) {
    if (queue == NULL || queue->Count >= queue->Size) {
        return 0; // Queue d?y ho?c không t?n t?i
    }
    //DisableAllInterrupt();
    queue->Buffer[queue->Rear] = data;
    queue->Rear = (queue->Rear + 1) % queue->Size;
    queue->Count++;
    //EnableAllInterrupt();
    return 1;
}


uint32_t Queue_Send_FromISR(Queue_t* queue, uint8_t data) {
    if (queue == NULL || queue->Count >= queue->Size) return 0;

    queue->Buffer[queue->Rear] = data;
    queue->Rear = (queue->Rear + 1) % queue->Size;
    queue->Count++;
    TriggerSV_Call_Interrupt();
    return 1;
}


uint32_t Queue_Receive_FromISR(Queue_t* queue, uint8_t* data) {
    if (queue == NULL || queue->Count == 0) {
        return 0; // Queue r?ng ho?c không t?n t?i
    }

    // KHÔNG g?i TaskENTER_CRITICAL ? dây
    *data = queue->Buffer[queue->Front];
    queue->Front = (queue->Front + 1) % queue->Size;
    queue->Count--;

    return 1;
}


uint32_t Queue_Receive(Queue_t* queue, uint8_t* data) {
    if (queue == NULL || queue->Count == 0) {
        return 0; // Queue r?ng ho?c không t?n t?i
    }
   // DisableAllInterrupt();
    *data = queue->Buffer[queue->Front];
    queue->Front = (queue->Front + 1) % queue->Size;
    queue->Count--;
	//EnableAllInterrupt();
    return 1;
}

uint8_t isQueueEmpty(Queue_t* queue){
	if(queue == NULL) return 1; // Nếu queue không tồn tại thì coi như rỗng
	return (queue->Count == 0);
}

uint8_t isQueueFull(Queue_t* queue){
	if(queue == NULL) return 0; // Queue NULL thì không coi là đầy
	return (queue->Count == queue->Size);
}


