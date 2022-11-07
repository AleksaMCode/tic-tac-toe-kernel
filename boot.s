; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
FLAGS    equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

; Declare a multiboot header that marks the program as a kernel. These values are documented in the multiboot standard.
; The bootloader will search for this signature in the first 8 KiB of the kernel file, aligned at a 32-bit boundary.
section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .data
var dw 0

section .bss
align 16
stack_bottom:
resb 2048 
stack_top:

section .text
extern monitor_write_dec
extern monitor_clear
global start:function (start.end - start)
extern main
start:
	mov esp, stack_top
	cli ; clear interrupt enable in eflags
	call main
	jmp $
.hang:  hlt
	jmp .hang
.end:

global hang
hang:
	hlt ; halt instruction
	jmp hang