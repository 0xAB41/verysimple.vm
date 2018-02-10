#include<stdio.h>
#include "vsvm.h"
#include "instruction_set.h"

int main(int argc, char *argv[]) {
    uint32_t instructions[] = {
            VERYSIMPLE_VM_ICONST, 10,
            VERYSIMPLE_VM_ICONST, 20,
            VERYSIMPLE_VM_IADD,
            VERYSIMPLE_VM_PRINT,
            VERYSIMPLE_VM_HALT
    };
    int size = sizeof(instructions) / sizeof(instructions[0]);
    run(instructions, size, 0);
    return 0;
}
