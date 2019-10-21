#include <kernel.h>

#pragma once

// Since this is all emulated, we'll be fiendishly tight on memory.
// Probably won't matter for my purposes though 

extern void *_HEAP_START_;

typedef struct _chunk {
	_chunk *next;
	uint8_t flags; // Reserved
	void *data; 
} _chunk_t;

void mman_init(void *, void*);
void *malloc(size_t);
void free(void *);
