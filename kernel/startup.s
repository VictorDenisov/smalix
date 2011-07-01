.text
.code32

.extern kernel_main
.globl _start
_start:
	movl $0x200000-4, %esp
	call kernel_main

#vim: noexpandtab
