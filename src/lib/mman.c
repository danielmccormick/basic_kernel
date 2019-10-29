#include <mman.h>

void mman_init() {
	mman_head = _HEAP_START_;
	mman_head->flags = MCHUNCK_INITIALIZED;
}


// no recombinations for now
void *malloc(size_t size) {
	int pad = 0;
	size_t min_chunk_size = 2*sizeof(size_t)+2*sizeof(uint8_t)+sizeof(chunk_t*)+size;
       	if (pad = (min_chunk_size%4)) {
		pad = 4-pad;
		size += pad;
		min_chunk_size += pad;
	
	}
	if (!mman_head) {
		mman_init();
	}
	_chunk_t trav* = mman_head;
	while (trav->flags != MCHUNK_INITIALIZED &&
		!(trav->flags == MCHUNK_FREED && trav->size >= min_chunk_size) {
		trav = trav->next;	
	}
	if (trav->flags = MCHUNK_FREED) {
		trav->flags &= (~MCHUNK_FREED);
		trav->flags |= (MCHUNK_ALLOCATED);
		return &(trav->data);
	}
	else if (&(trav->data)+(min_chunk_size-1) >= _HEAP_END) { return (void*)NULL; }
	trav->size = size;
	trav->flags &= (~MCHUNK_INITIALIZED);
	trav->flags |= MCHUNK_ALLOCATED;
	trav->next = (&(trav->data)+min(chunk_size-1));
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
