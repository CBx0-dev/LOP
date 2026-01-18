#include "gc.h"

#include <stdlib.h>

#include "object.h"

typedef struct ShadowStack
{
    struct ShadowStack* next;
    void*** frame;
    size_t size;
} ShadowStack;

typedef struct PointerList
{
    struct PointerList* next;
    void* ptr;
    size_t size;
    short marked;
    short type;
} PointerList;

ShadowStack* shadow_stack = NULL;
PointerList* ptr_list = NULL;

void gc_register_frame(void** frame_ptr[], const size_t frame_size)
{
    ShadowStack* frame = malloc(sizeof(ShadowStack));
    frame->frame = frame_ptr;
    frame->size = frame_size;
    frame->next = shadow_stack;

    shadow_stack = frame;
}

void gc_pop_frame(void)
{
    if (shadow_stack == NULL)
    {
        return;
    }

    ShadowStack* frame = shadow_stack;
    shadow_stack = shadow_stack->next;
    free(frame);
}

static size_t allocated_memory = 0;

void* gc_malloc(const size_t size, const short type)
{
    PointerList* item = malloc(sizeof(PointerList));
    if (!item)
    {
        // Try to collect objects
        gc_mark();
        gc_sweep();

        item = malloc(sizeof(PointerList));
        if (!item)
        {
            return NULL;
        }
    }

    item->ptr = malloc(size);
    item->size = size;
    item->marked = 0;
    item->type = type;

    if (!item->ptr)
    {
        free(item);
        return NULL;
    }

    item->next = ptr_list;
    ptr_list = item;

    allocated_memory += sizeof(PointerList) + size;
    return item->ptr;
}


void gc_free(const void* ptr)
{
    PointerList* previous_item = NULL;
    PointerList* current = ptr_list;
    while (current)
    {
        if (current->ptr == ptr)
        {
            if (previous_item)
            {
                previous_item->next = current->next;
            }
            else
            {
                ptr_list = current->next;
            }

            allocated_memory -= sizeof(PointerList) - current->size;
            free(current->ptr);
            free(current);
            return;
        }

        previous_item = current;
        current = current->next;
    }
}

static PointerList* gc_get_ptr(const void* ptr)
{
    PointerList* item = ptr_list;
    while (item)
    {
        if (item->ptr == ptr)
        {
            return item;
        }
        item = item->next;
    }

    return NULL;
}

static void gc_mark_ptr(const void* ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    PointerList* item = gc_get_ptr(ptr);
    // Not tracked by us, so we leave it as is, or
    // the item was already marked and therefore don't
    // need to be re-evaluated
    if (item == NULL || item->marked)
    {
        return;
    }

    item->marked = 1;
    if (item->type == GC_ALLOC_TYPE_OBJECT)
    {
        const ObjectType* type = OBJECT_TYPEOF(ptr);
        type->trace(ptr, gc_mark_ptr);
        return;
    }
}

static void gc_mark_frame(const ShadowStack* frame)
{
    for (size_t i = 0; i < frame->size; i++)
    {
        void* ptr = *frame->frame[i];
        if (ptr == NULL)
        {
            continue;
        }

        PointerList* item = gc_get_ptr(ptr);
        // Not tracked by us, so we leave it as is
        if (item == NULL)
        {
            continue;
        }

        // "!item->marked" -> Cut of already walked branches
        if (!item->marked && item->type == GC_ALLOC_TYPE_OBJECT)
        {
            item->marked = 1;
            const ObjectType* type = OBJECT_TYPEOF(ptr);
            type->trace(ptr, gc_mark_ptr);
            continue;
        }

        item->marked = 1;
    }
}

void gc_mark()
{
    const ShadowStack* frame = shadow_stack;
    while (frame)
    {
        gc_mark_frame(frame);
        frame = frame->next;
    }
}

void gc_sweep()
{
    PointerList* previous = NULL;
    PointerList* current = ptr_list;

    while (current)
    {
        if (current->marked)
        {
            current->marked = 0;
            previous = current;
            current = current->next;
            continue;
        }

        PointerList* to_free = current;
        if (previous)
        {
            previous->next = current->next;
        }
        else
        {
            ptr_list = current->next;
        }
        current = current->next;

        allocated_memory -= sizeof(PointerList) - to_free->size;
        free(to_free->ptr);
        free(to_free);
    }
}

void gc_mark_sweep()
{
    gc_mark();
    gc_sweep();
}
