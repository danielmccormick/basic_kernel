#include "kernel.h"

// set one entry
short vga_enter(unsigned char c, unsigned char front_colour, unsigned char back_colour) {
	unsigned char upper_bits = back_colour << 4; 
	unsigned char lower_bits = c;
	unsigned short ax_reg = (upper_bits << 8);
	ax_reg |= c;
	return ax_reg;
}

// empty buffer
void clear_vga_buffer(short **buff, unsigned char front, unsigned char back) {
	short it;
	for (it = 0; it < BUFSIZE; it++) {
		(*buff)[i] = vga_enter(0, front,back);
	}
}

// initializer
void vga_init(unsigned char front, unsigned char back) {
	vga_buffer = VGAADDRESS; // set ptr
	clear_vga_buffer(*vga_buffer,front,back); // clear buffer
}

void kernel_entry() {
	vga_init(0,0);
	vga_buffer[0] = vga_entr('A',1,0); // hope this all works
}
