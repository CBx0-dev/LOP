cmake_minimum_required(VERSION 4.1)
project(LOP C)

set(CMAKE_C_STANDARD 11)

include_directories(runtime)

add_executable(gen
        runtime/main.c
        runtime/gc.c
        runtime/gc.h
        runtime/object.c
        runtime/object.h
        runtime/primitive.h
        runtime/string_obj.c
        runtime/string_obj.h
        runtime/fs.c
)
