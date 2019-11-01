#include "kernel.h"
#include "lib/mman.c"

void kernel_entry() {
	vga_init(WHITE,BLACK);
	printf("Hello World");
	draw_unit_box(30,40,WHITE);
	while(1);
	return;
}
