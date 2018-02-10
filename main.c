#include<stdio.h>
#include "vsvm.h"
#include "instruction_set.h"

int main(int argc, char *argv[]) {
    int branching[] = {
            VERYSIMPLE_VM_ICONST, 10,
            VERYSIMPLE_VM_ICONST, 20,
            VERYSIMPLE_VM_LT,
            VERYSIMPLE_VM_BRT, 8,
            VERYSIMPLE_VM_HALT,
            VERYSIMPLE_VM_ICONST, 30,
            VERYSIMPLE_VM_HALT
    };
    int size = sizeof(branching) / sizeof(branching[0]);
    run(branching, size, 0);
    return 0;
}
