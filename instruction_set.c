#include "instruction_set.h"

const int VERYSIMPLE_VM_HALT = 0;
const int VERYSIMPLE_VM_ICONST = 1;
const int VERYSIMPLE_VM_IADD = 2;
const int VERYSIMPLE_VM_ISUB = 3;
const int VERYSIMPLE_VM_IMUL = 4;
const int VERYSIMPLE_VM_LT = 5;
const int VERYSIMPLE_VM_GT = 6;
const int VERYSIMPLE_VM_EQ = 7;
const int VERYSIMPLE_VM_NEQ = 8;
const int VERYSIMPLE_VM_BRT = 9;
const int VERYSIMPLE_VM_BRF = 10;
const int VERYSIMPLE_VM_CALL = 11;
const int VERYSIMPLE_VM_RET = 12;
const int VERYSIMPLE_VM_LOAD = 13;
const int VERYSIMPLE_VM_PRINT = 15;