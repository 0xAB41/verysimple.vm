#ifndef VERYSIMPLE_VM_INSTRUCTION_SET_H
#define VERYSIMPLE_VM_INSTRUCTION_SET_H

enum {
    VERYSIMPLE_VM_HALT, //halt execution
    VERYSIMPLE_VM_ICONST, //push constant on stack
    VERYSIMPLE_VM_IADD, //integer addition
    VERYSIMPLE_VM_ISUB, //integer subtraction
    VERYSIMPLE_VM_IMUL, //integer multiplication
    VERYSIMPLE_VM_ILT, //integer less than
    VERYSIMPLE_VM_IGT, //integer greather than
    VERYSIMPLE_VM_IEQ, //integer equals operation
    VERYSIMPLE_VM_INEQ, //integer not equals
    VERYSIMPLE_VM_BRT, //branch if true
    VERYSIMPLE_VM_BRF, //branch if false
    VERYSIMPLE_VM_CALL, //call function
    VERYSIMPLE_VM_RET, //return from function
    VERYSIMPLE_VM_LOAD, //load function argument on to stack
    VERYSIMPLE_VM_PRINT, //print the value at stack pointer
};

#endif //VERYSIMPLE_VM_INSTRUCTION_SET_H
