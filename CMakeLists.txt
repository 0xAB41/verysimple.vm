cmake_minimum_required(VERSION 3.9)
project(verysimple_vm)

set(CMAKE_CXX_STANDARD 11)

add_executable(verysimple_vm
        main.c
        makefile
        src/vsvm.c
        include/vsvm.h include/logger.h src/logger.c include/instruction_set.h src/math.c include/math.h)
