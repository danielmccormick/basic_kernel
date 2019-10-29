#pragma once
#include <kernel.h>

void *memcpy(void *dst, const void *src, const size_t num) {
	// unsafe, but basic
	if (!src || !dst || !num) { return dst; }
	size_t cnt = 0;
	while (cnt < num) { (uint8_t *)dst[cnt] = (uint8_t *)src[cnt++];}
	return dst;	
}
