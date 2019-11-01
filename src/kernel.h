#include "lib/utils.h"

#ifndef KERNEL_H
#define KERNEL_H

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

#endif

