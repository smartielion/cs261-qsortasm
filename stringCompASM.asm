
SECTION	.data
		
SECTION	.bss

SECTION	.text

global	stringCompASM

;Casey Gilray
;April 1st, 2013
;String comparison
;This program outputs True if the first string entered is greater than(comes after) the second
;If the string is the same, or comes before, it will output False
;
stringCompASM:
		push esi
		push ebp					;build the stack frame
 		mov ebp, esp		
		mov eax, ebx
		mov edx,  ecx

		mov     esi, 0
top:
		mov bl, [eax + esi]		;load first string into al
		mov cl,	[edx + esi]		;move al into ah
								;load the second string into al


comparisons:
		cmp bl,cl					;subtract ah brom bl
		jl less					;if bl is less than 0(string1 less) jump to false prompt
		jg great					;if bl is greater than z(string1 greater) jump to true prompt
		cmp bl, 0				;if ah is `\0`, print the false prompt
		je equ					;if it is end of line for string1, then string 1 is always less than or directly equal to string 2		
		inc esi
		jmp top					;until max number of max number of digits is reached.
		

		
less:
		mov eax, -1
		pop ebp
		pop esi
		ret

equ:
		mov		eax, 0			; write
		pop 		ebp
		pop esi
		ret					;unconditional jump to end.

great:
		mov		eax, 1			; write
		pop 		ebp
		pop esi
		ret


