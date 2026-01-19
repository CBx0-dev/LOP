#ifndef LOP_GC_H
#define LOP_GC_H

#include <stdint.h>
#include <stddef.h>

#define GC_ALLOC_TYPE_ATOMIC 0
#define GC_ALLOC_TYPE_OBJECT 1

#define GC_FRAME_NAME gc_roots

#define GC_LOCAL(var) ((void**)&(var))

#define GC_FRAME_INIT(n, locals...) \
    void **GC_FRAME_NAME[] = { locals }; \
    gc_register_frame(GC_FRAME_NAME, n)

#define GC_FRAME_DESTROY \
    gc_pop_frame()

void gc_register_frame(void** frame_ptr[], size_t frame_size);

void gc_pop_frame(void);

void* gc_malloc(size_t size, short type);

void gc_free(const void* ptr);

void gc_mark();

void gc_sweep();

#endif
