#include "string_obj.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String_impl* String;

/**
 * Temporary string definition should be moved into managed code when achievable
 *
 * Strings are always immutable. The buff could be a heap pointer or a stack pointer of a directly string literal
 */
struct String_impl
{
    ObjectType* __type_header__;
    uchar* buff;
    i32 length;
};

static void String_trace(const void* _obj, gc_mark_fn mark)
{
    const String obj = (String)_obj;
    mark(obj->buff);
}

ObjectType String_type = {
    .trace = String_trace
};

String string_concat(String left, String right)
{
    i32 new_size = left->length + right->length;
    uchar* new_buff = gc_malloc(new_size + 1, GC_ALLOC_TYPE_ATOMIC);

    memcpy(new_buff, left->buff, left->length);
    memcpy(new_buff + left->length, right->buff, right->length);
    new_buff[new_size] = '\0';

    return STRING_CTOR(String_impl, String_type, new_buff, new_size);
}

String string_substring(String str, i32 start, i32 end)
{
    i32 new_size = end - start;
    if (new_size < 0 || new_size > str->length)
    {
        printf("string_substring out of bounds call\n");
        exit(1);
    }

    uchar* new_buff = gc_malloc(new_size + 1, GC_ALLOC_TYPE_ATOMIC);

    memcpy(new_buff, str->buff + start, new_size);
    new_buff[new_size] = '\0';

    return STRING_CTOR(String_impl, String_type, new_buff, new_size);
}

uchar string_char_at(String str, i32 index)
{
    if (index < 0 || index >= str->length)
    {
        return '\0';
    }

    return str->buff[index];
}

bool string_equals(String left, String right)
{
    if (left->length != right->length)
    {
        return 0;
    }

    for (i32 i = 0; i < left->length; i++)
    {
        if (left->buff[i] != right->buff[i])
        {
            return 0;
        }
    }

    return 1;
}

void string_dump(String str)
{
    printf("%s\n", (char*)str->buff);
}