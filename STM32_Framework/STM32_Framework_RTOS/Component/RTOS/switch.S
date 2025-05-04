.syntax unified
.cpu cortex-m3
.thumb

.global PendSV_Handler
.extern Task_GetCurrentCPU
.extern Task_GetNextCPU
.extern isIdle_Task
.extern Task

.equ R4_RS,   32
.equ R5_RS,   36
.equ R6_RS,   40
.equ R7_RS,   44
.equ R8_RS,   48
.equ R9_RS,   52
.equ R10_RS,  56
.equ R11_RS,  60
.equ SP_RS,   64

.type PendSV_Handler, %function
PendSV_Handler:

    bl Task_GetCurrentCPU      @ R0 = pointer to current task context

    ldr r2, =isIdle_Task       @ Load address of isIdle_Task
    ldr r2, [r2]               @ Load isIdle_Task value
    cmp r2, #1                 @ Check if idle task
    beq IS_IDLE_TASK

STR_CPU:
    @ Store current task's CPU context
    str r4,  [r0, #R4_RS]
    str r5,  [r0, #R5_RS]
    str r6,  [r0, #R6_RS]
    str r7,  [r0, #R7_RS]
    str r8,  [r0, #R8_RS]
    str r9,  [r0, #R9_RS]
    str r10, [r0, #R10_RS]
    str r11, [r0, #R11_RS]
    mrs r1,  psp
    str r1,  [r0, #SP_RS]

GET_CPU:
    bl Task_GetNextCPU         @ R0 = pointer to next task context

    @ Load next task's CPU context
    ldr r4,  [r0, #R4_RS]
    ldr r5,  [r0, #R5_RS]
    ldr r6,  [r0, #R6_RS]
    ldr r7,  [r0, #R7_RS]
    ldr r8,  [r0, #R8_RS]
    ldr r9,  [r0, #R9_RS]
    ldr r10, [r0, #R10_RS]
    ldr r11, [r0, #R11_RS]
    ldr r1,  [r0, #SP_RS]
    msr psp, r1

    ldr r3, =Task
    cmp r0, r3                 @ Check if next task is idle task
    beq BREAK

BREAK:
    mov lr, #0xFFFFFFFD
    bx lr

IS_IDLE_TASK:
    movs r12, #2
    msr control, r12

    ldr r2, [r0, #SP_RS]
    msr psp, r2

    ldr r1, =isIdle_Task
    movs r2, #0
    str r2, [r1]

    b STR_CPU

.size PendSV_Handler, .-PendSV_Handler
