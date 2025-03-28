;    PRESERVE8
;	AREA rtos_function, CODE, READONLY, ALIGN=3
;	
;	
;    EXPORT PendSV_Handler
;	EXTERN Task_GetCurrentCPU
;	EXTERN Task_GetNextCPU
;	;SP here - R0 - R1 - R2 - R3 - R12 - RA - LR  - EPSR
;PendSV_Handler
;	; Save current CPU
;	BL	Task_GetCurrentCPU
;	STR R4,		[R0,#4*8 ]
;	STR R5,		[R0,#4*9 ]
;	STR R6,		[R0,#4*10]
;	STR R7,		[R0,#4*11]
;	STR R8,		[R0,#4*12]
;	STR R9,		[R0,#4*13]
;	STR R10,	[R0,#4*14]
;	STR R11,	[R0,#4*15]
;	STR SP,		[R0,#4*16]
;	
;	BL Task_GetNextCPU
;	CMP R0,#0
;	BEQ BREAK
;	
;	;LOAD next CPU
;	LDR R4,		[R0,#4*8 ]
;	LDR R5,		[R0,#4*9 ]
;	LDR R6,		[R0,#4*10]
;	LDR R7,		[R0,#4*11]
;	LDR R8,		[R0,#4*12]
;	LDR R9,		[R0,#4*13]
;	LDR R10,	[R0,#4*14]
;	LDR R11,	[R0,#4*15]
;	LDR SP,		[R0,#4*16]

;BREAK
;	LDR	R0,=0xfffffff9
;	MOV LR,R0
;	BX	LR	
;	
;;	
;    END
