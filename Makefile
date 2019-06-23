FLAGS = -m32 -nostdlib -fno-builtin -fno-exceptions -fno-leading-underscore -ffreestanding -Wall -Wextra
TARGETS = boot.o kernel.o

default: link

package: link
	grub-file --is-x86-multiboot BasicOS.bin
	mkdir -p ./isodir/boot/grub
	mv BasicOS.bin ./isodir/boot/.
	cp grub.cfg ./isodir/boot/grub/.
	grub-mkrescue -o BasicOS.iso isodir

link: $(TARGETS)
	ld -m elf_i386 -nostdlib -T linker.ld $(TARGETS) -o BasicOS.bin 

kernel.o: kernel.c
	gcc kernel.c $(FLAGS) -o kernel.o

boot.o: boot.s
	as --32 boot.s -o boot.o

.PHONY: clean
clean: 
	rm -f *.o *.out
