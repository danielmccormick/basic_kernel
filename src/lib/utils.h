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

void *memset(void *str, const int c, const size_t n) {
	if (!str || !n) { return str; }
	size_t cnt = 0;
	while (cnt < n) { 
		((unsigned char*)str)[cnt] = (unsigned char)c; 
		cnt++;	
	}
	return str;
}

void sleep_n_cycles (size_t timer_count) {
	timer_count >>= 2;
	while(timer_count--) { asm volatile("nop"); }
}
