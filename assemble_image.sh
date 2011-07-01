#!/bin/bash

dd if=/dev/zero of=bzImage.img count=768
dd if=boot/boot.img of=bzImage.img conv=notrunc
bootloader_size=`du -b boot/boot.img|awk '{ print $1 }'`
dd if=kernel/kernel.img of=bzImage.img obs=1 seek=730 conv=notrunc
