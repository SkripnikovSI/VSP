global _fun

_fun:
	mov ecx, [esp+12]
	mov eax, ecx
	mov ecx, 2
	mul ecx
	mov ecx, eax
	fld1
	fld1
	faddp st1, st0
	fldz
	fld qword [esp+4]
	fld qword [esp+4]
	fmulp st1, st0
	fsubp st1, st0
	fld1
	fld qword [esp+4]
	fld qword [esp+4]
l:
	fld st4
	faddp st3, st0
	fld st3
	fmulp st2, st0
	fld st1
	fdiv st0, st3
	faddp st1, st0
	dec ecx
	jnz l

	ret