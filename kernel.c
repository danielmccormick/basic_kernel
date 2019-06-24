#include "kernel.h"

// set one entry
uint16_t vga_entry(uint8_t c, uint8_t front_colour, uint8_t back_colour) {
	uint8_t colour_bits = back_colour << 4; // Upper Bits will be background colour 
	colour_bits |= front_colour;
	uint16_t ax_reg = (colour_bits << 8);
	ax_reg |= c;
	return ax_reg;
}

// empty buffer
void clear_vga_buffer(uint16_t **buff, uint8_t front, uint8_t back) {
	uint32_t it; // Iterate through
	for (it = 0; it < BUFSIZE; it++) {
		(*buff)[it] = vga_entry(0, front,back);
	}
}

// initializer
void vga_init(uint8_t front, uint8_t back) {
	vga_buffer = (void *)VGAADDRESS; // set ptr
	clear_vga_buffer(&vga_buffer,front,back); // clear buffer
}

void printf(char *s) {
	int i;
	for (i = 0; s[i] != '\0'; i++) {
		vga_buffer[i] = vga_entry(s[i],WHITE,BLACK);
	}
}

void kernel_entry() {
	vga_init(WHITE,BLACK);
	printf("Hello, World!\0");
	return;
}
