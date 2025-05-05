	;; Royce Nogales, GW00371
	;; HW9, CMSC313, 5/4/25

	SECTION .data
	msg db 'Hello World!', 0Ah

	SECTION .text
	global _start

_start:
	mov edx, 13
	mov ecx, msg
	mov ebx, 1
	mov eax, 4
	int 80h
	
