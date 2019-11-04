FLAGS = -m32 -ffreestanding -Wall -Wextra 
TARGETS = boot.o kernel.o

default: link

package: link
	grub-file --is-x86-multiboot BasicOS.bin
	mkdir -p ./isodir/boot/grub
	cp BasicOS.bin ./isodir/boot/.
	cp grub.cfg ./isodir/boot/grub/.
	grub-mkrescue -o BasicOS.iso isodir

link: $(TARGETS)
	ld -m elf_i386 -T linker.ld $(TARGETS) -o BasicOS.bin -nostdlib

kernel.o: kernel.c
	gcc  $(FLAGS) -c kernel.c -o kernel.o

boot.o: boot.s
	as --32 boot.s -o boot.o

run: package
	qemu-system-x86_64 -cdrom BasicOS.iso

.PHONY: clean
clean: 
	rm -f *.o *.out *.iso *.bin
