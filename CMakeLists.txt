cmake_minimum_required(VERSION 3.10)
project(EoSTool C)

enable_language(Fortran)
#set(CMAKE_FORTRAN_COMPILER "/usr/bin/gfortran")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DF90_DEBUG")
set(CMAKE_Fortran_FLAGS "${CMAKE_Fortran_FLAGS} -DF90_DEBUG -cpp")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
link_libraries(m z)
set(SRC third_party/InputParser.c eos_state.c test.c Tools.c tillotson_eos.f90)

add_executable(EoSTool main.c ${SRC})

