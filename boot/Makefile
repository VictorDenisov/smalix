main: kernel bootblock.s sb.s
	as -o bootblock.o bootblock.s
	ld -Ttext=0 --oformat binary bootblock.o -o bootblock.img 
	as -o sb.o sb.s
	ld -Ttext=700 --oformat binary sb.o -o sb.img

	dd if=/dev/zero of=boot.img count=64
	dd if=bootblock.img of=boot.img conv=notrunc
	dd if=sb.img of=boot.img seek=1 conv=notrunc
	dd if=kernel.img of=boot.img obs=1 seek=730 conv=notrunc

kernel: ktty.c kernel.c startup.s ioports.c intslib.c handlers.c
	as --32 -o startup.o startup.s
	gcc -m32 -fno-stack-protector -ffreestanding -c -o ktty.o ktty.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o kernel.o kernel.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o handlers.o handlers.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o intslib.o intslib.c
	gcc -m32 -fno-stack-protector -ffreestanding -c -o ioports.o ioports.c
	ld -melf_i386 --oformat binary -Ttext=0x200000 -o kernel.img startup.o ktty.o intslib.o ioports.o handlers.o kernel.o

clean:
	rm *.o
	rm *.img
