cmake_minimum_required(VERSION 4.1)
project(LOP C)

set(CMAKE_C_STANDARD 99)

include_directories(runtime)

add_library(runtime STATIC
    runtime/gc.c
    runtime/gc.h
    runtime/object.c
    runtime/object.h
    runtime/primitive.h
)

add_executable(lopc
        output/entry.c
        output/main.c
        output/string_obj.c
        output/string_obj.h
        output/fs.c
)


target_link_libraries(lopc PRIVATE runtime)