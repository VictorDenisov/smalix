.text
.code16
.globl _start
_start:

	cli

	movw $0, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movw $0x700, %sp

	sti

	movw $msg_intro, %si
	call kputs

	movw $msg_entering_pmode, %si
	call kputs

	movb $1, %ah
	movb $0x20, %ch
	int $0x10

	movb $0x11, %al
	outb $0x20
	movb $0x20, %al
	outb $0x21
	movb $0x04, %al
	outb $0x21
	movb $0x01, %al
	outb $0x21

	cli

	lgdt gd_reg

	inb $0x92
	or $2, %al
	outb $0x92

	movl %cr0, %eax
	orb $1, %al
	movl %eax, %cr0

	ljmp $0x8,$_protected

kputs:
	
	pusha

kputs_loop:
	lodsb
	test %al, %al
	jz kputs_quit
	movb $0x0e, %ah
	int $0x10
	jmp kputs_loop

kputs_quit:

	popa
	ret

.code32

_protected:
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss

	movl $kernel_binary, %esi

	movl $0x4000, %ecx

	rep movsl

	jmp 0x200000

gdt:
.short 0, 0, 0, 0

.byte 0xff, 0xff, 0x00, 0x00, 0x00, 0x9a, 0xcf, 0x00

.byte 0xff, 0xff, 0x00, 0x00, 0x00, 0x92, 0xcf, 0x00

gd_reg:
.short 8192
.long gdt

msg_intro:	
.ascii "Secondary bootloader received control"
.byte 0x0A, 0x0D, 0

msg_entering_pmode:	
.ascii "Entering protected mode..."
.byte 0x0A, 0x0D, 0

kernel_binary:

#vim: noexpandtab
