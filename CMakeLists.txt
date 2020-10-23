cmake_minimum_required(VERSION 3.17)
project(Xorshift_simd C)

set(CMAKE_C_STANDARD 11)

set(SOURCES xorwow.c)

add_library(Xorshift_simd ${SOURCES})

target_compile_options(Xorshift_simd INTERFACE -msse2)

enable_testing()

add_executable(xorshift_test test.c ${SOURCES})
