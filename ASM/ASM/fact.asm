section .text
global _fact

_fact:
	mov ecx, [esp+4]
	mov eax, 1

lp:
	mul ecx
	sub ecx, 1
	jg lp

	ret