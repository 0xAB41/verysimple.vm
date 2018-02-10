#include "include/vsvm.h"
#include "include/instruction_set.h"
#include "include/logger.h"

int main(int argc, char *argv[]) {
    log_set_level(VERYSIMPLE_VM_LOG_DEBUG);
    int factorial[] = {
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_ICONST, 2,
            VERYSIMPLE_VM_LT,
            VERYSIMPLE_VM_BRF, 10,
            VERYSIMPLE_VM_ICONST, 1,
            VERYSIMPLE_VM_RET,
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_ICONST, 1,
            VERYSIMPLE_VM_ISUB,
            VERYSIMPLE_VM_CALL, 0, 1,
            VERYSIMPLE_VM_IMUL,
            VERYSIMPLE_VM_RET,
            VERYSIMPLE_VM_ICONST, 5,
            VERYSIMPLE_VM_CALL, 0, 1,
            VERYSIMPLE_VM_PRINT,
            VERYSIMPLE_VM_HALT
    };
    int size = sizeof(factorial) / sizeof(factorial[0]);
    run(factorial, size, 22);
    return 0;
}
