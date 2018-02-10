#include "include/vsvm.h"
#include "include/instruction_set.h"
#include "include/logger.h"

void run_factorial(int n) {
    int factorial[] = {
            //if n < 2 return 1
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_ICONST, 2,
            VERYSIMPLE_VM_LT,
            VERYSIMPLE_VM_BRF, 10,
            VERYSIMPLE_VM_ICONST, 1,
            VERYSIMPLE_VM_RET,
            //else return n * factorial(n-1)
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_ICONST, 1,
            VERYSIMPLE_VM_ISUB,
            VERYSIMPLE_VM_CALL, 0, 1,
            VERYSIMPLE_VM_IMUL,
            VERYSIMPLE_VM_RET,
            //entry point: call factorial(n)
            VERYSIMPLE_VM_ICONST, n,
            VERYSIMPLE_VM_CALL, 0, 1,
            VERYSIMPLE_VM_PRINT,
            VERYSIMPLE_VM_HALT
    };
    int size = sizeof(factorial) / sizeof(factorial[0]);
    run(factorial, size, 22);
}

void run_fibonacci(int n) {
    int fibonacci[] = {
            //if n == 0 return 0
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_ICONST, 0,
            VERYSIMPLE_VM_EQ,
            VERYSIMPLE_VM_BRF, 10,
            VERYSIMPLE_VM_ICONST, 0,
            VERYSIMPLE_VM_RET,
            //if n < 3 return 1
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_ICONST, 3,
            VERYSIMPLE_VM_LT,
            VERYSIMPLE_VM_BRF, 20,
            VERYSIMPLE_VM_ICONST, 1,
            VERYSIMPLE_VM_RET,
            //else return fibonacci(n-1) + fibonacci(n-2)
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_ICONST, 1,
            VERYSIMPLE_VM_ISUB,
            VERYSIMPLE_VM_CALL, 0, 1,
            VERYSIMPLE_VM_LOAD, -3,
            VERYSIMPLE_VM_ICONST, 2,
            VERYSIMPLE_VM_ISUB,
            VERYSIMPLE_VM_CALL, 0, 1,
            VERYSIMPLE_VM_IADD,
            VERYSIMPLE_VM_RET,
            //call fibonacci(n)
            VERYSIMPLE_VM_ICONST, n,
            VERYSIMPLE_VM_CALL, 0, 1,
            VERYSIMPLE_VM_PRINT,
            VERYSIMPLE_VM_HALT
    };
    int size = sizeof(fibonacci) / sizeof(fibonacci[0]);
    run(fibonacci, size, size-7);
}

int main(int argc, char *argv[]) {
    log_set_level(VERYSIMPLE_VM_LOG_DEBUG);
    run_factorial(10);
    run_fibonacci(10);
    return 0;
}
