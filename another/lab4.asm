CODE 	SEGMENT
	ASSUME CS:CODE, DS:DATA, ES:DATA, SS:MSTACK
 
START:
	JMP BEGIN

RStack	DB	32	DUP (0)

;-------------------------------------------------------------------------

DATA	SEGMENT
	INI_MENU_S	DB 'RESIDENT HAD BEEN LOADED SUCCESSFULLY.',0DH,0AH,'$'
	ERR_MENU_S	DB 'ERROR LOADING A RESIDENT! RESIDENT IS ALREADY INSTALLED.',0DH,0AH,'$'
	DEL_MENU_S	DB 'RESIDENT HAD BEEN UNLOADED SUCCESSFULLY.',0DH,0AH,'$'
DATA	ENDS

;-------------------------------------------------------------------------

MSTACK	SEGMENT STACK
	DW 512 DUP (?)
MSTACK	ENDS

;-------------------------------------------------------------------------

ROUT 	PROC FAR 
	JMP R_CODE
	
	IDENT_S	DW 1234H
	CHECK_B	DB 0 
	CLOCK_I	DB 0
	
	KEEP_CS  	DW 0
	KEEP_IP  	DW 0 
	KEEP_PSP 	DW 0
	KEEP_SS  	DW 0
	KEEP_SP  	DW 0
	
R_CODE:
	MOV KEEP_SS, SS 
	MOV KEEP_SP, SP
	MOV AX, CS
	MOV SS, AX
	MOV SP, 20H
	
	PUSH AX 
	PUSH DX
	PUSH BX
	PUSH CX
	
	CMP CHECK_B, 1
	JE BACKUP_INT
	
	MOV AH, 03H 
	MOV BH, 00H
	INT 10h 
	
	PUSH DX 
	
	MOV DL,	00H 
	MOV AH,	02H
	MOV BH,	00H
	INT 10h
	
	CMP CLOCK_I, 10H
	JL 	LT_16
	MOV CLOCK_I, 0H	
	JMP	LT_4
	
LT_16:
	CMP CLOCK_I, 0CH
	JL	LT_12
	MOV AL, 2DH
	JMP	P_SYM
	
LT_12:
	CMP CLOCK_I, 08H
	JL	LT_8
	MOV AL, 5CH
	JMP	P_SYM
	
LT_8:
	CMP CLOCK_I, 04H
	JL	LT_4
	MOV AL, 7CH
	JMP	P_SYM
	
LT_4:
	MOV AL, 2FH
	
P_SYM:
	PUSH AX
	PUSH BX
	PUSH CX
	MOV AH, 09H
	MOV CX, 1 
	MOV BX, 0004H 
	INT 10H 
	INC CLOCK_I
	POP CX
	POP BX
	POP AX
	
	POP DX
	
	MOV AH,	02H
	MOV BH,	00H
	INT 10h
	
	JMP R_EXIT
	
BACKUP_INT:  
	CLI 
	MOV DX,	KEEP_IP
	MOV AX,	KEEP_CS
	MOV DS,	AX 
	MOV AH,	25H 
	MOV AL,	1CH 
	INT 21H 
	MOV ES, KEEP_PSP  
	MOV ES, ES:[2CH] 
	MOV AH, 49H
	INT 21H
	MOV ES, KEEP_PSP  
	MOV AH, 49H
	INT 21H	
	STI
		
R_EXIT:
	POP CX
	POP BX
	POP DX
	POP AX 
	POPF
		
	MOV SS, KEEP_SS 
	MOV SP, KEEP_SP
	IRET
ROUT ENDP

;-------------------------------------------------------------------------

END_OF_ROUT:

CHECK_R PROC 
	MOV AH, 35H
	MOV AL, 1CH 
	INT 21H
	
	MOV SI, OFFSET IDENT_S
	SUB SI, OFFSET ROUT
	
	CMP ES:[BX+SI], 1234H
	JNE R_INST
	
	PUSH ES
	PUSH AX
	MOV AX, KEEP_PSP
	MOV ES, AX
	CMP BYTE PTR ES:[82H],'/'
	JNE R_NDEL
	CMP BYTE PTR ES:[83H],'u'
	JNE R_NDEL
	CMP BYTE PTR ES:[84H],'n'
	JE R_DEL
	
R_DEL:
	POP AX
	POP ES
	MOV BYTE PTR ES:[BX+SI+2],1 
	MOV DX, OFFSET DEL_MENU_S
	CALL WRITE
	RET
	
R_NDEL: 
	POP AX
	POP ES
	MOV DX, OFFSET ERR_MENU_S
	CALL WRITE
	RET	
	
R_INST:
	PUSH DS
	MOV AH, 35H
	MOV AL, 1CH 
	INT 21H
	MOV KEEP_IP, BX
	MOV KEEP_CS, ES 
	
	MOV DX, OFFSET ROUT 
	MOV AX, SEG ROUT
	MOV DS, AX 
	MOV AH, 25H 
	MOV AL, 1CH 
	INT 21H 
	POP DS
	
	MOV DX, OFFSET INI_MENU_S
	CALL WRITE
	MOV DX, OFFSET END_OF_ROUT
	MOV CL,	4 
	SHR DX,	CL
	INC DX	
	ADD DX,	CODE 
	SUB DX,	KEEP_PSP 
	SUB AL,AL
	MOV AH,31H 
	INT 21H
CHECK_R ENDP

;-------------------------------------------------------------------------

WRITE PROC NEAR 
	PUSH AX
	MOV AH, 09H
	INT 21H
	POP AX
	RET
WRITE ENDP

;-------------------------------------------------------------------------

BEGIN:
	MOV AX, DATA
	MOV DS, AX
	MOV KEEP_PSP, ES
	
	CALL CHECK_R
	SUB AL, AL
	MOV AH, 4Ch 
	INT 21H
CODE ENDS
END START
