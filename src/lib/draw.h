#include "utils.h"

// define vga buffer
uint16_t *vga_buffer; // buffer is 16 bits ..
#define VGAADDRESS 0xB8000
#define BUFSIZE 2200

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

// set one entry
uint16_t vga_entry(uint8_t c, uint8_t front_colour, uint8_t back_colour) {
	uint8_t colour_bits = back_colour; // Upper Bits will be background colour 
	colour_bits <<= 4;
	colour_bits |= front_colour;
	uint16_t ax_reg = (colour_bits);
	ax_reg <<= 8;
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
	vga_buffer = (uint16_t *)VGAADDRESS; // set ptr
	clear_vga_buffer(&vga_buffer,front,back); // clear buffer
}

void printf(char *s) {
	int i;
	for (i = 0; s[i]; i++) {
		vga_buffer[i] = vga_entry(s[i],WHITE,BLACK);
	}
}

void draw_unit_box(uint16_t x, uint16_t y, uint8_t colour) {
    size_t index = 80*y+x;
    vga_buffer[index] = vga_entry(218,colour,colour);
}