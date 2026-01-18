#ifndef LOP_OBJECT_H
#define LOP_OBJECT_H

#include "primitive.h"
#include "gc.h"

typedef void (*gc_mark_fn)(const void* obj);
typedef void (*gc_trace_fn)(const void* obj, gc_mark_fn mark);

typedef struct
{
    gc_trace_fn trace;
} ObjectType;

#define OBJECT_TYPEOF(ptr) (*((ObjectType**)ptr))

static inline void* __object_ctor(const size_t size, ObjectType* header)
{
    void** obj = gc_malloc(size, GC_ALLOC_TYPE_OBJECT);
    obj[0] = header;
    return obj;
}

#define OBJECT_CTOR(impl, header) __object_ctor(sizeof(struct impl), &header)

void object_empty_trace(const void* obj, gc_mark_fn mark);

#endif
