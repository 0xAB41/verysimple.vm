#include "vsvm.h"
#include "instruction_set.h"
#include <stdio.h>

struct vm_state {
    uint32_t *instructions;
    int program_counter;
    uint32_t *stack;
    int stack_pointer;
};

void print_stack(struct vm_state *state) {
    printf("    [stack]");
    for (int i = 0; i <= state->stack_pointer; i++) {
        printf("->%d", state->stack[i]);
    }
    printf("\n");
}

uint32_t fetch(struct vm_state *state) {
    return state->instructions[state->program_counter++];
}

uint32_t decode(uint32_t instruction) {
    return instruction;
}

uint32_t pop(struct vm_state *state) {
    return state->stack[state->stack_pointer--];
}

int push(struct vm_state *state, uint32_t value) {
    return (state->stack[++state->stack_pointer] = value) == value;
}

uint32_t peek(struct vm_state *state) {
    return state->stack[state->stack_pointer];
}

int execute(struct vm_state *state, uint32_t decoded_instruction) {
    int ret_val = 1;
    print_stack(state);
    if (decoded_instruction == VERYSIMPLE_VM_ICONST) {
        uint32_t constant = state->instructions[state->program_counter++];
        push(state, constant);
        printf("iconst %d\n", constant);
    } else if (decoded_instruction == VERYSIMPLE_VM_IADD) {
        uint32_t b = pop(state);
        uint32_t a = pop(state);
        push(state, a + b);
        printf("iadd %d %d\n", a, b);
    } else if (decoded_instruction == VERYSIMPLE_VM_PRINT) {
        printf("print %d\n", peek(state));
    } else if (decoded_instruction == VERYSIMPLE_VM_HALT) {
        printf("halt\n");
    } else {
        printf("Unknown instruction %d\n", decoded_instruction);
        ret_val = 0;
    }
    print_stack(state);
    return ret_val;
}

void run(uint32_t *instructions, int instructions_size, int entry_point) {
    uint32_t stack[100];
    struct vm_state state = {
            .stack = &stack,
            .stack_pointer = -1,
            .program_counter = entry_point,
            .instructions = instructions
    };
    int is_execution_successful = 1;
    while (is_execution_successful && state.program_counter < instructions_size) {
        uint32_t instruction = fetch(&state);
        uint32_t decoded_instruction = decode(instruction);
        is_execution_successful = execute(&state, decoded_instruction);
    }
    return;
}
