    PRESERVE8
    AREA rtos_function, CODE, READONLY, ALIGN=3

    EXPORT PendSV_Handler
    EXTERN Task_GetCurrentCPU
    EXTERN Task_GetNextCPU
    EXTERN isIdle_Task
    EXTERN Task
        
R4_RS   EQU 32
R5_RS   EQU 36  
R6_RS   EQU 40
R7_RS   EQU 44
R8_RS   EQU 48
R9_RS   EQU 52  
R10_RS  EQU 56
R11_RS  EQU 60
SP_RS   EQU 64

PendSV_Handler
    ; Save current CPU context
    BL Task_GetCurrentCPU

    ; Check isIdle_Task flag
    LDR R2, =isIdle_Task
    LDR R2, [R2]
    CMP R2, #1
    BEQ IS_IDLE_TASK

STR_CPU
    ; Store current task's CPU context
    STR R4,  [R0, #R4_RS]
    STR R5,  [R0, #R5_RS]
    STR R6,  [R0, #R6_RS]
    STR R7,  [R0, #R7_RS]
    STR R8,  [R0, #R8_RS]
    STR R9,  [R0, #R9_RS]
    STR R10, [R0, #R10_RS]
    STR R11, [R0, #R11_RS]
    MRS R1,  PSP 
    STR R1,  [R0, #SP_RS]

GET_CPU
    ; Get next CPU context
    BL Task_GetNextCPU

    ; Load next CPU context
    LDR R4,  [R0, #R4_RS]
    LDR R5,  [R0, #R5_RS]
    LDR R6,  [R0, #R6_RS]
    LDR R7,  [R0, #R7_RS]
    LDR R8,  [R0, #R8_RS]
    LDR R9,  [R0, #R9_RS]
    LDR R10, [R0, #R10_RS]
    LDR R11, [R0, #R11_RS]
    LDR R1,  [R0, #SP_RS]
    MSR PSP, R1

    ; Check if the next task is Task_idle (assume Task_idle = Task[0])
    LDR R3, =Task
    CMP R0, R3
    BEQ BREAK  

BREAK
    MOV LR, #0xFFFFFFFD
    BX LR


IS_IDLE_TASK
    ; Initialize SP for idle task
    MOV R12, #2
    MSR CONTROL, R12

    LDR R2, [R0, #SP_RS]
    MSR PSP, R2
    LDR R1, =isIdle_Task
    MOV R2, #0
    STR R2, [R1]
    B STR_CPU ; <-- Ðã s?a l?i dúng nhãn

    END
