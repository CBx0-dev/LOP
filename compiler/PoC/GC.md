# Garbage Collector

The language uses a mark-and-sweep garbage collector to manage memory efficiently.

The garbage collector is responsible for automatically reclaiming memory that is no longer in use by the program.

The GC only handles memory allocated through the GC API. This is used by memory-sensitive types, including everything
that is an `Object`.

We implement a stop-the-world mark-and-sweep GC. Every object exposes a `trace` handler that marks itself and its
children items.

## Marking Phase

During the marking phase, the GC traverses all reachable objects starting from the "roots". An object is reachable if it
is referenced by a root or by another reachable object.

The GC uses two main structures:

- `ShadowStack`: A stack of local variables (roots) registered by functions.
- `PointerList`: A global list of all memory blocks allocated by the GC.

### Allocation Types

When allocating memory via `gc_malloc(size, type)`, two types are supported:

- `GC_ALLOC_TYPE_ATOMIC`: Used for memory that does not contain any pointers to other GC-managed objects (e.g., raw
  buffers, strings). The GC will not scan these blocks.
- `GC_ALLOC_TYPE_OBJECT`: Used for memory that represents an object and may contain pointers. These blocks must be declared
  such as in the Object PoC defined.

## Root Variable Tracking

To ensure that local variables (roots) are correctly identified by the garbage collector during the marking phase, the
generated C code explicitly registers and unregisters these variables.

We achieve this by maintaining a **shadow stack** of roots. Each function that uses GC-managed objects pushes its local
references onto this shadow stack upon entry and pops them before returning.

### GC Root API

The `gc.h` header provides macros to simplify frame management:

- `GC_FRAME_INIT(n)`: Allocates a frame for `n` pointers and registers it on the shadow stack.
- `GC_FRAME_ACCESS(index, type)`: Provides access to a specific pointer in the current frame.
- `GC_FRAME_DESTROY`: Pops the current frame from the shadow stack.

When a LOP function is transpiled to C, it might look like this:

```c
#include "gc.h"
#include "object.h"

typedef struct
{
    ObjectType* type;
    int some_value;
    void* some_memory;
} TestObject;

void test_object_trace(const void* obj, gc_mark_fn mark)
{
    TestObject* test_obj = (TestObject*)obj;

    // Ensure some_memory is also marked
    mark(test_obj->some_memory);
}

static ObjectType TestObjectType = {
    .trace = test_object_trace
};

void foo(void)
{
    // Initialize frame with 1 slot
    GC_FRAME_INIT(1);
    
    // Get a pointer to the slot (as TestObject**)
    TestObject** var1 = GC_FRAME_ACCESS(0, TestObject);

    *var1 = NULL;

    // Allocate an object
    *var1 = gc_malloc(sizeof(TestObject), ALLOC_TYPE_OBJECT);
    (*var1)->type = &TestObjectType;
    (*var1)->some_value = 42;
    
    // Allocate atomic memory (no pointers inside)
    (*var1)->some_memory = gc_malloc(1024, ALLOC_TYPE_ATOMIC);

    // Always destroy frame before returning
    GC_FRAME_DESTROY;
    return;
}

int main(void)
{
    foo();
    
    // Trigger GC manually
    gc_mark();
    gc_sweep();

    return 0;
}
```

## Global variables

Global variables are tracked by defining a global stack frame (or multiple frames) that contains all global references,
ensuring they are always treated as roots.

## Implementation Details

### Shadow Stack

The shadow stack is a linked list of `ShadowStack` structures, where each node points to an array of pointers on the
real C stack.

### Pointer List

The `PointerList` tracks every allocation. Each entry stores:

- The actual pointer to allocated memory.
- A `marked` flag used during the mark phase.
- The `type` (Atomic or Object).

During `gc_sweep()`, any entry in the `PointerList` that is not `marked` is `free`'d, and its entry is removed from the
list.