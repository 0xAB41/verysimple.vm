# verysimple.vm
A very simple bytecode virtual machine implementation in C

- Stack based VM
- Works off a single data type (Integer)
- Supports function calls (including recursion)

## Instruction Set
```
    /**
     * Halts the execution
     * Single word instruction
     */
    VERYSIMPLE_VM_HALT,

    /**
     * Loads the constant following this op on to stack
     * Two word instruction
     * ICONST <Integer>
     */
    VERYSIMPLE_VM_ICONST,

    /**
     * Performs Integer addition on two values on top of stack
     * Replaces the operands with the result
     * Single word instruction
     */
    VERYSIMPLE_VM_IADD,

    /**
     * Performs Integer subtraction on two values on top of stack
     * Replaces the operands with the result
     * Single word instruction
     */
    VERYSIMPLE_VM_ISUB,

    /**
     * Performs Integer multiplication on two values on top of stack
     * Replaces the operands with the result
     * Single word instruction
     */
    VERYSIMPLE_VM_IMUL, //integer multiplication

    /**
     * Performs Integer less than comparision on two values on top of stack
     * Replaces the operands with the result (0 - false or 1 - true)
     * Single word instruction
     */
    VERYSIMPLE_VM_ILT,

    /**
     * Performs Integer greater than comparision on two values on top of stack
     * Replaces the operands with the result (0 - false or 1 - true)
     * Single word instruction
     */
    VERYSIMPLE_VM_IGT,

    /**
     * Performs Integer equals comparision on two values on top of stack
     * Replaces the operands with the result (0 - false or 1 - true)
     * Single word instruction
     */
    VERYSIMPLE_VM_IEQ,

    /**
     * Performs Integer greater than comparision on two values on top of stack
     * Replaces the operands with the result (0 - false or 1 - true)
     * Single word instruction
     */
    VERYSIMPLE_VM_INEQ,

    /**
     * Jumps to given program_counter location if top of the stack is a truthy value
     * Two word instruction
     * BRT <LOCATION>
     */
    VERYSIMPLE_VM_BRT,

    /**
     * Jumps to given program_counter location if top of the stack is a falsy value
     * Two word instruction
     * BRF <LOCATION>
     */
    VERYSIMPLE_VM_BRF,

    /**
     * Call the function at given location. The number of arguments the function expects
     * should be provided. Arguments are pop'ed from stack.
     * Three word instruction
     * CALL <LOCATION> <Number of fn Args>
     */
    VERYSIMPLE_VM_CALL,

    /**
     * Return from the function. Value on top of the stack is considered a return value and
     * preserved after stack unwinding
     * Single word instruction
     */
    VERYSIMPLE_VM_RET,

    /**
     * Loads the value relative to frame_pointer on to stack top
     * Two word instruction
     * LOAD <OFFSET>
     */
    VERYSIMPLE_VM_LOAD,

    /**
     * Prints the value on top of the stack
     * Single word instruction
     */
    VERYSIMPLE_VM_PRINT,
```

## Project Layout

```
.
├── README.md
├── include                  -header file includes
│   ├── instruction_set.h     -Instruction set
│   ├── logger.h
│   ├── math.h
│   └── vsvm.h
├── main.c                   -sample main containing factorial, fibonacci programs
└── src
    ├── logger.c
    ├── math.c
    └── vsvm.c
```

## Building & Running

Use `cmake` with in project directory to generate make file

```
cmake .
```

then

```
make
```

Include `vsvm.h` and run using 
```c
void run(int *instructions, int instructions_size, int entry_point, int stack_size);
```

Take a look at included `main.c` for couple of example programs(factorial and fibonacci)