cmake_minimum_required(VERSION 2.8.4)
project(tinymill)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.c)
add_executable(tinymill ${SOURCE_FILES})