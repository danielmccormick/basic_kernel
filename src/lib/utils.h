#pragma once

/* Type Definitions */
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef long int64_t;
typedef uint64_t size_t;
typedef int64_t ssize_t;

#define NULL 0


void *memcpy(void *dst, const void *src, const size_t num) {
	// unsafe, but basic
	if (!src || !dst || !num) { return dst; }
	size_t cnt = 0;
	while (cnt < num) { 
		((uint8_t *)dst)[cnt] = ((uint8_t *)src)[cnt];
		cnt++;
	}
	return dst;	
}
