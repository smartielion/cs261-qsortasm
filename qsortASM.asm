
SECTION	.data
		
SECTION	.bss

SECTION	.text

global	qsort
extern  	stringCompASM
extern 	strcmp

;i: equ [ebp - 4]
;j: equ [ebp - 8]

;Casey Gilray
;April 1st, 2013
;Quick Sort
;Steps through half the list at a time sorting recursivly
;
;

global qsortASM
;i = ebp - 4
;j = ebp - 8
;piv = ebp - 12
;eax = ebp + 4 = holds the array
;ebx= ebp+ 8 = holds the "left" integer
;ecx = ebp + 12 = hold the right register
;
;address within array = [eax + 4*i] array pointer plus 4 times the offset

qsortASM:
	push ebp
	mov ebp,esp			;seet up the stack frame
	sub esp, 12			;create space for locals
	mov eax, [ebp + 8]
	mov ebx, [ebp + 12]
	mov ecx , [ebp + 16]
	add ecx,ebx
	shr ecx, 1			;set up pivot right + left /2
	mov edx, [eax + 4*ecx]
	mov [ebp-12], edx
	mov [ebp - 4], ebx		;set ebp - 4 = 0
	mov ecx , [ebp + 16]
	mov [ebp - 8], ecx		;set ebp - 8 = right

loop:
	mov esi, [ebp -4]	;set esi to i


loopI:
	cmp esi, [ebp -8]		;if i >= j, recurse
	jge recurse
	mov ebx, [eax + 4*esi]		;move [eax + 4*esi] into ebx
	mov ecx, [ebp - 12] 		;move pivot into ecx
	call stringCompASM			;call string comp value returned in ea
	cmp eax, 0				;if eax >= 0, goto loopj
	mov eax, [ebp + 8]
	jge loopJ	
	inc esi				;inc esi
	jmp loopI					;j loopI

loopJ:
	mov [ebp-4], esi			;stores i into ebp - 4
	mov esi, [ebp-8]			;puts ebp -8 into esi as j
loopJAux:
	cmp esi, [ebp-4]			;if j <= i, recurse
	jle recurse	
	mov ebx, [eax + 4*esi]		;move [eax + 4*esi] into ebx
	mov ecx, [ebp -12]			; move pivot into ecx
	call stringCompASM			;cakk string comp, returned in eax
	cmp eax,0					; if eax <= 0, goto indCheck
	mov eax, [ebp + 8]
	jle indCheck	
	dec esi				;dec esi
	jmp loopJAux				;j loopJ Aux
	
indCheck:
	mov [ebp-8],esi		;save j
	mov ebx,[ebp-4]		; checks to see if i has gone past j
						;move i into ebx
						;j is in esi
	cmp ebx, esi			;comp eax and ebx
	jl wordSwap			;if comp >= 1, wordswap
	jmp recurse

wordSwap:
	mov esi, [ebp -4]		;set esi to i
	mov eax, [ebp+8]		;set eax as ebp + 4
	mov ebx, [eax + 4*esi]		;set ebx as eax + 4*esi
	mov edi, [ebp - 8]		;set edi to j
	mov ecx, [eax + 4*edi]	;set ecx to eax + 4*edi
	mov [eax + 4*edi],ebx	;move ebx into eax + 4*edi
	mov [eax + 4*esi],ecx	;move ecx into eax + 4*esi
	inc esi
	dec edi
	mov [ebp - 4], esi
	mov [ebp - 8], edi
	jmp loop				;continue to loop

recurse:
	mov [ebp -8],esi		;save j into esi to be safe

left:	;array,left,j
	mov esi, [ebp-8]		;move j into esi
	mov eax, [ebp+8]		;move array into eax
	mov ebx, [ebp+12]		;move left ionto ebx
	sub esi,ebx			;compare left and j
	cmp esi, 1
	jle right				;if they are same, jump to right
	mov esi, [ebp-8]
	push esi				;push esi
	push ebx				;push ebx
	push eax				;push eax
	call qsortASM			;call qsortASM
	pop eax
	pop ebx
	pop esi

right:	;array, i right
	mov esi, [ebp-4]	;move i into esi
	mov ebx, [ebp+16]	;move right ionto ebx
	sub ebx, esi			;compare right and i
	cmp ebx, 1
	jle return				;if they are same, jump to return
	mov ebx, [ebp+16]
	push ebx
	push esi
	push eax
	call qsortASM
	pop eax
	pop esi
	pop ebx

return:
	add esp, 12
	pop ebp
	ret

