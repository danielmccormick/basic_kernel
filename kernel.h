#ifndef KERNEL_H
#define KERNEL_H

/* Type Definitions */
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#define NULL 0

// define vga buffer
uint32_t *vga_buffer;
#define VGA_ADDRESS 0x0B8000
#define BUFSIZE 2200

#endif

