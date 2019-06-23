#ifndef KERNEL_H
#define KERNEL_H

/* Type Definitions */
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
#define NULL 0

// define vga buffer
uint16_t *vga_buffer; // buffer is 16 bits ..
#define VGAADDRESS 0x0B8000
#define BUFSIZE 2200

#endif

