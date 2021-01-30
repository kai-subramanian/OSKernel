as --32 boot.s -o boot.o

#compile kernel2.c file
gcc -m32 -c kernel2.c -o kernel2.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

#linking the kernel2 with kernel2.o and boot.o files
ld -m elf_i386 -T linker.ld kernel2.o boot.o -o MyOS.bin -nostdlib

#check MyOS.bin file is x86 multiboot file or not
grub-file --is-x86-multiboot MyOS.bin

#building the iso file
mkdir -p isodir/boot/grub
cp MyOS.bin isodir/boot/MyOS.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o MyOS.iso isodir

#run it in qemu
qemu-system-x86_64 -cdrom MyOS.iso
