#ifndef LOP_STRING_OBJ_H
#define LOP_STRING_OBJ_H

#include "object.h"

static inline void* __string_ctor(const size_t size, ObjectType* header, uchar* buff, i32 length)
{
    void** obj = __object_ctor(size, header);
    obj[1] = buff;
    *(i32*)&obj[2] = length;
    return obj;
}

#define STRING_CTOR(impl, header, buff, length) __string_ctor(sizeof(struct impl), &header, buff, length)

#endif