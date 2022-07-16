cmake_minimum_required(VERSION 3.10)
project(EoSTool C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
link_libraries(m z)
set(SRC third_party/InputParser.c eos_state.c test.c)

add_executable(EoSTool main.c ${SRC})

