cmake_minimum_required(VERSION 3.9)
project(verysimple_vm)

set(CMAKE_CXX_STANDARD 11)

add_executable(verysimple_vm
        main.c
        makefile
        README.md
        vsvm.c
        vsvm.h logger.h logger.c instruction_set.c instruction_set.h)
