#include "kernel.h"

// set one entry
short vga_entry(unsigned char c, unsigned char front_colour, unsigned char back_colour) {
	unsigned char colour_bits = back_colour << 4; // Upper Bits will be background colour 
	colour_bits |= front_colour;
	unsigned short ax_reg = (colour_bits << 8);
	ax_reg |= c;
	return ax_reg;
}

// empty buffer
void clear_vga_buffer(short **buff, unsigned char front, unsigned char back) {
	short it; // Iterate through
	for (it = 0; it < BUFSIZE; it++) {
		(*buff)[it] = vga_entry(0, front,back);
	}
}

// initializer
void vga_init(unsigned char front, unsigned char back) {
	vga_buffer = (void *)VGAADDRESS; // set ptr
	clear_vga_buffer(*vga_buffer,front,back); // clear buffer
}

void kernel_entry() {
	vga_init(0,0);
	vga_buffer[0] = vga_entry('A',1,0); // hope this all works
}
