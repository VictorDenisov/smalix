main:
	as -o bootblock.o bootblock.s
	ld -Ttext=0 --oformat binary bootblock.o -o bootblock.img 
	as -o sb.o sb.s
	ld -Ttext=700 --oformat binary sb.o -o sb.img

	dd if=/dev/zero of=boot.img count=4
	dd if=bootblock.img of=boot.img conv=notrunc
	dd if=sb.img of=boot.img seek=1 conv=notrunc

clean:
	rm *.o
	rm *.img
