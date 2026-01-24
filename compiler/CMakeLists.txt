cmake_minimum_required(VERSION 4.1)
project(LOP C)

set(CMAKE_C_STANDARD 11)

include_directories(runtime)

add_library(runtime STATIC
    runtime/gc.c
    runtime/gc.h
    runtime/object.c
    runtime/object.h
    runtime/primitive.h
)

add_executable(gen
        output/main.c
        output/string_obj.c
        output/string_obj.h
        output/fs.c
)

add_executable(gen2
        output/main2.c
        output/string_obj.c
        output/string_obj.h
        output/fs.c
)

target_link_libraries(gen PRIVATE runtime)
target_link_libraries(gen2 PRIVATE runtime)