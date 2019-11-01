#include "mman.h"

void mman_init() {
	mman_head_ = _HEAP_START_;
	mman_head_->flags = MCHUNK_INITIALIZED;
}


// no recombinations for now
void *malloc(size_t size) {
	int pad = 0;
	size_t min_chunk_size = 2*sizeof(size_t)+2*sizeof(uint8_t)+sizeof(_chunk_t*)+size;
       	if ( (pad = (min_chunk_size%4)) ) {
		pad = 4-pad;
		size += pad;
		min_chunk_size += pad;
	
	}
	if (!mman_head_) {
		mman_init();
	}
	_chunk_t *trav = mman_head_;
	while (trav->flags != MCHUNK_INITIALIZED &&
		!(trav->flags == MCHUNK_FREED && trav->size >= min_chunk_size)) {
		trav = trav->next;	
	}
	if (trav->flags == MCHUNK_FREED) {
		trav->flags &= (~MCHUNK_FREED);
		trav->flags |= (MCHUNK_ALLOCATED);
		return &(trav->data);
	}
	else if ((void*)&(trav->data)+(min_chunk_size-1) >= _HEAP_END_) { return (void*)0; }
	trav->size = size;
	trav->flags &= (~MCHUNK_INITIALIZED);
	trav->flags |= MCHUNK_ALLOCATED;
	trav->next = &(_chunk_t *)((trav->data)+(char*)(min_chunk_size-1));
	return &(trav->data);
}

void free(void *mdata) {
	char *m_chunk_flags = mdata;
	m_chunk_flags--;
	if (*m_chunk_flags & MCHUNK_INITIALIZED) {
		*m_chunk_flags &= (~MCHUNK_ALLOCATED);
		*m_chunk_flags |= (MCHUNK_FREED);
	}
}
