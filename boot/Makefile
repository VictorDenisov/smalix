boot.img: bootblock.img sb.img
	dd if=bootblock.img of=boot.img conv=notrunc
	dd if=sb.img of=boot.img seek=1 conv=notrunc

bootblock.o: bootblock.s
	as -o bootblock.o bootblock.s
bootblock.img: bootblock.o
	ld -Ttext=0 --oformat binary bootblock.o -o bootblock.img 

sb.o: sb.s
	as -o sb.o sb.s
sb.img: sb.o
	ld -Ttext=700 --oformat binary sb.o -o sb.img

clean:
	rm *.o
	rm *.img
