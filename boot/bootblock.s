.text
.code16

.equ CYLS_TO_READ, 10

#Error can have place due
.equ MAX_READ_ERRORS, 5

.globl _start
_start:


	cli
	movw %cs, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %ss
	movw $0x7c00, %sp

	sti

	#copy loader

	movw $0x07c0, %ax
	movw %ax, %ds

	movw $0x9000, %ax
	movw %ax, %es

	xorw %si, %si
	xorw %di, %di

	movw $128, %cx
	rep movsl

	jmp $0x9000,$start

start:

	movw %cs, %ax
	movw %ax, %ds
	movw %ax, %ss
	
# Report a message to user
	movw $msg_loading, %si
	call kputs

# Now read cylinder.
	movw $1, %di
	movw $0x290, %ax

	xorw %bx, %bx

loop:
	movw $0x50, %cx
	movw %cx, %es

	pushw %di

	shrw $1, %di
	setcb %dh
	movw %di, %cx
	xchg %ch, %cl

	popw %di

#all cylinders?
	cmpw $CYLS_TO_READ, %di
	je quit

	call kread_cylinder

	pusha
	pushw %ds

	movw $0x50, %cx
	movw %cx, %ds
	movw %ax, %es
	xorw %di, %di
	xorw %si, %si
	movw $0x2400, %cx
	rep movsb

	popw %ds
	popa

	incw %di
	addw $0x240, %ax
	jmp loop
quit:

	movw $0x50, %ax
	movw %ax, %es
	movw $0, %bx
	movb $0, %ch
	movb $0, %dh
	call kread_cylinder

	ljmp $0x0000,$0x0700

kread_cylinder: 
	
	movb $0, error_counter

	pusha

#inform user
	movw $msg_cylinder, %si
	call kputs

	movb %ch, %ah
	call kputhex

	movw $msg_head, %si
	call kputs

	movb %dh, %ah
	call kputhex

	movw $msg_crlf, %si
	call kputs

	popa
	pusha

kread_cylinder_start:
	movb $0x02, %ah
	movb $18, %al
	movb $1, %cl

	int $0x13
	jc read_error

	popa
	ret # return of kread_cylinder but not end

error_counter:
.byte 0

read_error:
	incb error_counter
	movw $msg_reading_error, %si
	call kputs
	call kputhex

	movw $msg_crlf, %si
	call kputs

	movb error_counter, %al
	cmpb $MAX_READ_ERRORS, %al
	jg kread_cylinder_start

	#fail

	movw $msg_giving_up, %si
	call kputs
	hlt
	jmp .

#end of kread_cylinder

hex_table:
.ascii "0123456789ABCDEF"

kputhex: #output hex function

	pusha
	xorw %bx, %bx
	movb %ah, %bl
	andb $0xf0, %bl
	shrb $4, %bl
	movb hex_table(%bx), %al
	call kputchar

	movb %ah, %bl
	andb $0x0f, %bl
	movb hex_table(%bx), %al
	call kputchar

	popa
	ret # end of kputhex

kputchar:
	
	pusha

	movb $0x0e, %ah
	int $0x10
	popa
	ret # end of kputchar

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
	ret # end of kputs


msg_loading:
.ascii "the Operating System is loading..."
.byte 0x0a, 0x0d, 0

msg_cylinder:
.ascii "Cylinder:"
.byte 0

msg_head:
.ascii ", head:"
.byte 0

msg_reading_error:
.ascii "Error reading from floppy. Errcode:"
.byte 0

msg_giving_up:
.ascii "Too many errors, giving up"

.byte 0x0a, 0x0d

.ascii "Reboot your system, please"
.byte 0

msg_crlf:
.byte 0x0a, 0x0d, 0

. = 510 + _start

.byte 0xaa, 0x55
