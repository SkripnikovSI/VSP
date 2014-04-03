global _mydiv

_mydiv:
	mov edx, 0
	mov eax, [esp+4]
	mov ebx, [esp+8]
	div ebx
	

	ret