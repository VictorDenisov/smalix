main:
	as -o bootblock.o bootblock.s
	ld -Ttext=7c00 --oformat binary bootblock.o -o bootblock.bin 
