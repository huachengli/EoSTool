cmake_minimum_required(VERSION 3.19)
project(EoSTool C)

set(CMAKE_C_STANDARD 99)
link_libraries(m)

set(SRC third_party/InputParser.c
        eos_state.c test.c test.h)

add_executable(EoSTool main.c ${SRC})