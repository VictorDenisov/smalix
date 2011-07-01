bzImage: 
	make -C boot
	make -C kernel
	./assemble_image.sh

clean:
	make -C boot clean
	make -C kernel clean
	rm *.img
