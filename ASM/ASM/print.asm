global _print

_print:
	mov ecx, [esp+8]
	mov eax, [esp+12]

	; flags
	push dword 0; width  esp + 22
	push word 0; sign esp + 21
	push word 0; - and + esp + 19,18
	push word 0; ' ' and '0' esp + 17,16
	; number
	push dword 0; esp + 12
	push dword 0; esp + 8
	push dword 0; esp + 4
	push dword 0; esp

	mov [esp+34], ebx
	mov ebx, eax

	flags:
		cmp [ecx], byte 0
		je end_next_digits
		cmp [ecx], byte '-'
		jne flag1
		mov [esp+19], byte -1
		inc ecx
		jmp flags
		flag1:
			cmp [ecx], byte '+'
			jne flag2
			mov [esp+18], byte -1
			inc ecx
			jmp flags
			flag2:
				cmp [ecx], byte ' '
				jne flag3
				mov [esp+17], byte -1
				inc ecx
				jmp flags
				flag3:
					cmp [ecx], byte '0'
					jne end_flags
					mov [esp+16], byte -1
					inc ecx
					jmp flags
	end_flags:

	; width
	xor eax, eax
	cmp [ecx], byte 0
	je end_next_digits 
	next_digit:
		mov edx, 10
		mul edx
		mov dl, [ecx]
		sub edx, '0'
		add eax, edx
		inc ecx
		cmp [ecx], byte 0
		jne next_digit 
	mov [esp+22], eax
	end_next_digits:

	; size of string
	mov ecx, ebx
	cmp [ecx], byte 0
	je end_size_of_string
	
		; get sign
		cmp [ecx], byte '-'
		jne size_of_string
		mov [esp+21], byte -1
		inc ecx
		inc ebx

	size_of_string:
		inc ecx
		cmp [ecx], byte 0
		jne size_of_string
	end_size_of_string:

	sub ecx, ebx
	add ebx, ecx
	
	; string to 4 dword
	xor eax, eax
	cmp ecx, 0
	je end_string_to_4_dword

	string_to_4_dword:
		dec	ebx

		mov dl, [ebx]
		sub dl, '0'	
		cmp dl, 9
		jle end_first_number_is_char
		sub	dl, 7
		cmp dl, 15
		jle end_first_number_is_char
		sub	dl, 32
		end_first_number_is_char:

		mov dh, dl
		xor dl, dl

		dec ecx
		cmp ecx, 0
		je l1
		dec	ebx

		mov dl, [ebx]
		sub dl, '0'	
		cmp dl, 9
		jle end_second_number_is_char
		sub	dl, 7
		cmp dl, 15
		jle end_second_number_is_char
		sub	dl, 32
		end_second_number_is_char:

		dec ecx

		l1:
		shl dl, 4
		add dl, dh
		mov [esp + eax], dl
		inc eax
		
		cmp ecx, 0
		jne string_to_4_dword
	end_string_to_4_dword:
	
	; make nonnegative
	mov eax, [esp+12]
	and eax, 080000000h
	jz nonnegative 
		not dword [esp]
		not dword [esp+4]
		not dword [esp+8]
		not dword [esp+12]
		add [esp], dword 1
		adc [esp+4], dword 0
		adc [esp+8], dword 0
		adc [esp+12], dword 0
		xor [esp+21], byte -1
	nonnegative:
	
	mov ecx, esp
	add ecx, 12

	push esi;
	push edi;
	push ebp;
	mov esi, [esp+42]; out_buf
	mov edi, esp
	add edi, 28
	mov ebp, 0; length

	; is zero
	mov eax, [ecx]
	or eax, [ecx-4]
	or eax, [ecx-8]
	or eax, [ecx-12]
	jz end_digit_on_stack1

	digit_on_stack:
		; is zero
		mov eax, [ecx]
		or eax, [ecx-4]
		or eax, [ecx-8]
		or eax, [ecx-12]
		jz end_digit_on_stack2

		; div by ten
		xor edx, edx
		mov ebx, 10
		mov eax, [ecx]
		div ebx
		mov [ecx], eax
		mov eax, [ecx-4]
		div ebx
		mov [ecx-4], eax
		mov eax, [ecx-8]
		div ebx
		mov [ecx-8], eax
		mov eax, [ecx-12]
		div ebx
		mov [ecx-12], eax

		add dx, '0'
		push dx

		inc ebp
		jmp digit_on_stack
	end_digit_on_stack1:
		push word '0'
		inc ebp
		mov [edi + 5], byte 0
	end_digit_on_stack2:
	; dword width edi + 6
	; byte  sign  edi + 5
	; byte  -     edi + 3
	; byte  +     edi + 2
	; byte  ' '   edi + 1
	; byte  '0'   edi

	; sign on stack
	mov ax, '-'
	cmp [edi+5], byte -1
	je signed
		mov ax, '+'
		cmp [edi+2], byte -1
		je signed
			mov ax, ' '
			cmp [edi+1], byte -1
			je signed
				xor eax, eax
				jmp unsigned
	signed:
		inc ebp
	unsigned:

	xor ecx, ecx
	cmp ebp, [edi+6]
	jae without_additions
		mov ecx, [edi+6]
		sub ecx, ebp
		cmp [edi+3], byte -1
		je without_additions
			cmp [edi], byte 0
			je spaces
				fill_with_zeros:
					push word '0'
					inc ebp
					dec ecx
					jnz fill_with_zeros 
				jmp without_additions 
			spaces:
				cmp ax, 0
				je fill_with_spaces
				push ax
				xor eax, eax
				fill_with_spaces:
					push word ' '
					inc ebp
					dec ecx
					jnz fill_with_spaces 	
			jmp without_additions
	without_additions:

	cmp ax, 0
	je without_sing
	push ax
	without_sing:

	cmp ebp, 0
	je end_digit_to_char
	digit_to_char:
		pop ax	
		mov [esi], al
		inc esi
		dec ebp
		jnz digit_to_char
	end_digit_to_char:

	cmp ecx, 0
	je end_without_endspaces
	without_endspaces:
		mov [esi], byte ' '
		inc esi
		dec ecx
		jnz without_endspaces
	end_without_endspaces:

	mov [esi], byte 0

	
	pop ebp;
	pop edi;
	pop esi;

	mov ebx, [esp+34]
	add esp, 26

	ret


