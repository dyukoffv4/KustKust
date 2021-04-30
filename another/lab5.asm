CODE	SEGMENT
	ASSUME CS:CODE, DS:DATA, ES:DATA, SS:MSTACK

START:
	JMP BEGIN
	
RStack	DB 	32 	DUP (0)

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

	SIGNATURE_STRING	DW 1235H
	KEEP_IP		DW 0
	KEEP_CS		DW 0
	KEEP_PSP		DW 0

R_CODE:
	PUSH AX
	PUSH DX
	PUSH DS
	PUSH ES
	
	IN AL, 60H

	; q -> w
	CMP AL, 10H
	JE Q_TO_W

	; w -> e
	CMP AL, 11H
	JE W_TO_E

	; e -> r
	CMP AL, 12H
	JE E_TO_R
		
	; r -> t
	CMP AL, 13H
	JE R_TO_T
		
	; t -> y
	CMP AL, 14H
	JE T_TO_Y
	
	; y -> q
	CMP AL, 15H
	JE Y_TO_Q
		
	; else
	JMP DEFAULT

Q_TO_W:
	MOV CL,'W'
	CALL USER_ROUT
	JMP TO_USER_ROUT
		
W_TO_E:
	MOV CL,'E'
	CALL USER_ROUT
	JMP TO_USER_ROUT
		
E_TO_R:
	MOV CL,'R'
	CALL USER_ROUT
	JMP TO_USER_ROUT
		
R_TO_T:
	MOV CL,'T'
	CALL USER_ROUT
	JMP TO_USER_ROUT
		
T_TO_Y:
	MOV CL,'Y'
	CALL USER_ROUT
	JMP TO_USER_ROUT
	
Y_TO_Q:
	MOV CL,'Q'
	CALL USER_ROUT
	JMP TO_USER_ROUT
		
DEFAULT:
	PUSHF
	CALL DWORD PTR CS:KEEP_IP
				
TO_USER_ROUT:
	POP ES
	POP DS
	POP DX
	POP AX 
	IRET
ROUT 	ENDP

;-------------------------------------------------------------------------

USER_ROUT	PROC
	MOV AX, 0040h
	MOV ES, AX
	IN AL, 61H
	MOV AH, AL
	OR AL, 80H
	OUT 61H, AL
	XCHG AH, AL
	OUT 61H, AL
	MOV AL, 20H
	OUT 20H, AL
		
WRITE_TO_BUF:
	MOV AH, 05H
	MOV CH, 00H
	INT 16H
	OR AL, AL
	JZ UR_EXIT
	
	CLI
	MOV AX, ES:[1AH]
	MOV ES:[1CH], AX
	STI
	JMP WRITE_TO_BUF
		
UR_EXIT: 
	RET
USER_ROUT	ENDP

;-------------------------------------------------------------------------

BACKUP_INT PROC
	PUSH DS
	
	CLI	
	MOV DX,ES:[BX+SI+2]
	MOV AX,ES:[BX+SI+4]
	MOV DS,AX
	MOV AH,25H
	MOV AL,09H
	INT 21H 
	PUSH ES
	MOV ES,ES:[BX+SI+6]
	MOV ES,ES:[2CH]
	MOV AH,49H         
	INT 21H
	POP ES
	MOV ES,ES:[BX+SI+6]
	MOV AH, 49H
	INT 21H	
	STI
	
	POP DS
	RET
BACKUP_INT ENDP 

;-------------------------------------------------------------------------

END_OF_ROUT:

CHECK_R PROC
	MOV AH,35H
	MOV AL,09H
	INT 21H 

	MOV SI, OFFSET SIGNATURE_STRING
	SUB SI, OFFSET ROUT 
	
	CMP ES:[BX+SI], 1235H 
	JNE CR_NINS 
	
	PUSH ES
	PUSH AX
	MOV AX, KEEP_PSP
	MOV ES, AX
	CMP BYTE PTR ES:[82H],'/'
	JNE CR_NDEL
	CMP BYTE PTR ES:[83H],'u'
	JNE CR_NDEL
	CMP BYTE PTR ES:[84H],'n'
	JE CR_DEL

CR_DEL:
	POP AX
	POP ES
	CALL BACKUP_INT
	MOV DX, OFFSET DEL_MENU_S
	CALL WRITE
	RET
		
CR_NDEL:
	POP  AX
	POP  ES
	MOV  DX, OFFSET ERR_MENU_S
	CALL WRITE
	RET
		
CR_NINS:
	PUSH DS
	MOV AH, 35H
	MOV AL, 09H
	INT 21H
	MOV KEEP_IP, BX
	MOV KEEP_CS, ES
	
	MOV DX, OFFSET ROUT 
	MOV AX, SEG ROUT
	MOV DS, AX
	MOV AH, 25H
	MOV AL, 09H
	INT 21H
	POP DS
	
	MOV  DX, OFFSET INI_MENU_S
	CALL WRITE
	MOV DX, OFFSET END_OF_ROUT
	MOV CL, 4
	SHR DX, CL
	INC DX	 				
	ADD DX, CODE 			
	SUB DX, KEEP_PSP 		
	SUB AL, AL
	MOV AH, 31H
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
	MOV  AX, data
	MOV  DS, AX
	MOV  KEEP_PSP, ES
	
	CALL CHECK_R
	
	xor  AL,AL
	MOV  AH,4CH
	INT  21H
	
END_BYTE:
	RET
CODE	ENDS
END	START
