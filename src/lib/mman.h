#include "utils.h"
#pragma once

// Since this is all emulated, we'll be fiendishly tight on memory.
// Probably won't matter for my purposes though 

#define MCHUNK_INITIALIZED 1
#define MCHUNK_ALLOCATED 2
#define MCHUNK_FREED 4

extern void *_HEAP_START_;
extern void *_HEAP_END_;

typedef struct _chunk {
	size_t size;
	struct _chunk *next;
	uint8_t flags; // Reserved
	uint8_t data; // placeholder, all memory from &data to next  
} _chunk_t;

_chunk_t *mman_head_ = 0;

void mman_init();
void *malloc(size_t);
void free(void *);