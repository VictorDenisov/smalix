main: kernel bootblock.s sb.s
	as -o bootblock.o bootblock.s
	ld -Ttext=0 --oformat binary bootblock.o -o bootblock.img 
	as -o sb.o sb.s
	ld -Ttext=700 --oformat binary sb.o -o sb.img

	dd if=/dev/zero of=boot.img count=4
	dd if=bootblock.img of=boot.img conv=notrunc
	dd if=sb.img of=boot.img seek=1 conv=notrunc
	dd if=kernel.img of=boot.img obs=1 seek=730 conv=notrunc

kernel: ktty.c kernel.c startup.s
	as --32 -o startup.o startup.s
	gcc -m32 -ffreestanding -c -o ktty.o ktty.c
	gcc -m32 -ffreestanding -c -o kernel.o kernel.c
	ld -melf_i386 --oformat binary -Ttext=0x200000 -o kernel.img startup.o ktty.o kernel.o

clean:
	rm *.o
	rm *.img
