;heap_begin equ 0x103000
;heap_end equ 0x104000

section .heap
align 4
heap:
	resb 4096

section .text

[GLOBAL allocate]
extern monitor_write_dec
allocate:
	mov dword eax, heap ;1064960
	mov dword edx, [esp+4]
	jmp find_chunk

find_chunk:
	cmp dword [eax], 0
	je reserve_chunk
	add dword eax, [eax+4]
	add dword eax, 8
	;cmp eax, heap_end
	;jge no_space
	jmp find_chunk

reserve_chunk:
	mov dword [eax], 1
	mov dword ebx, [eax+4]
	mov dword [eax+4], edx
	mov dword ecx, eax
	add dword ecx, 8
	add dword ecx, edx
	sub dword ebx, edx
	sub dword ebx, 8
	mov dword [ecx], 0
	mov dword [ecx+4], ebx
	add dword eax, 8
	ret

[GLOBAL reset_heap]
reset_heap:
	mov dword eax, heap ;1064960
	mov dword [eax], 0
	mov dword [eax+4], 4088
	mov dword eax, 0
	ret

