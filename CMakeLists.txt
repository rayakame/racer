cmake_minimum_required(VERSION 3.20)
project(racer C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED, ON)
set(CMAKE_C_EXTENSIONS, OFF)

add_executable(racer main.c)
