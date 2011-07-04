kernel.img: ktty.o kernel.o startup.o ioports.o intslib.o handlers.o memory.o
	ld -melf_i386 --oformat binary -Ttext=0x200000 -o kernel.img startup.o ktty.o intslib.o ioports.o handlers.o memory.o kernel.o

startup.o: startup.s
	as --32 -o startup.o startup.s

ktty.o: ktty.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o ktty.o ktty.c

kernel.o: kernel.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o kernel.o kernel.c

handlers.o: handlers.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o handlers.o handlers.c

intslib.o: intslib.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o intslib.o intslib.c

ioports.o: ioports.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o ioports.o ioports.c

memory.o: memory.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o memory.o memory.c


clean:
	rm *.o
	rm *.img
