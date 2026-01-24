#include <string.h>

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

typedef struct ObjectList_impl* ObjectList;

extern ObjectList list_init();
extern void list_push(ObjectList list, Object obj);

extern i32 entry(ObjectList args);

i32 main(i32 argc, char* argv[])
{
    ObjectList args = list_init();
    for (i32 i = 0; i < argc; i++)
    {
        list_push(args, STRING_CTOR(String_impl, String_type, (uchar*)argv[i], strlen(argv[i])));
    }

    return entry(args);
}