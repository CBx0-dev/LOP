#include <stdio.h>

#include "object.h"
#include "string_obj.h"

typedef struct String_impl* String;

struct String_impl
{
    ObjectType* __type_header__;
    uchar* buff;
    i32 length;
};
extern ObjectType String_type;


String fs_read_file(String path)
{
    FILE* file = fopen((const char*)path->buff, "rb");
    fseek(file, 0, SEEK_END);
    i32 size = ftell(file);
    fseek(file, 0, SEEK_SET);
    uchar* buff = gc_malloc(size + 1, GC_ALLOC_TYPE_ATOMIC);
    fread(buff, sizeof(uchar), size, file);
    buff[size] = '\0';

    fclose(file);

    return STRING_CTOR(String_impl, String_type, buff, size);
}

Object fs_open_file(String path)
{
    FILE* file = fopen((const char*)path->buff, "wb");
    return file;
}

Object fs_get_stderr() {
    return stderr;
}

void fs_write_string(Object file, String str)
{
    fprintf(file, "%s", (const char*)str->buff);
}

void fs_write_int(Object file, i32 value)
{
    fprintf(file, "%i", value);
}

void fs_write_char(Object file, uchar c)
{
    fprintf(file, "%c", (const char)c);
}

void fs_close_file(Object file)
{
    fclose((FILE*)file);
}