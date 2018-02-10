#include "vsvm.h"
#include "instruction_set.h"
#include "logger.h"

struct vm_state {
    int *instructions;
    int program_counter;
    int *stack;
    int stack_pointer;
    int frame_pointer;
    int is_running;
};

void print_stack(struct vm_state *state) {
    log("    [stack]");
    for (int i = 0; i <= state->stack_pointer; i++) {
        log(" -> %d", state->stack[i]);
    }
    log("\n");
}

int fetch(struct vm_state *state) {
    return state->instructions[state->program_counter++];
}

int decode(int instruction) {
    return instruction;
}

int pop(struct vm_state *state) {
    return state->stack[state->stack_pointer--];
}

int push(struct vm_state *state, int value) {
    return (state->stack[++state->stack_pointer] = value) == value;
}

int peek(struct vm_state *state) {
    return state->stack[state->stack_pointer];
}

int execute(struct vm_state *state, int decoded_instruction) {
    int ret_val = 1;
    print_stack(state);
    if (decoded_instruction == VERYSIMPLE_VM_ICONST) {
        int constant = state->instructions[state->program_counter++];
        push(state, constant);
        log("iconst %d\n", constant);
    } else if (decoded_instruction == VERYSIMPLE_VM_IADD) {
        int b = pop(state);
        int a = pop(state);
        push(state, a + b);
        log("iadd %d %d\n", a, b);
    } else if (decoded_instruction == VERYSIMPLE_VM_ISUB) {
        int b = pop(state);
        int a = pop(state);
        push(state, a - b);
        log("isub %d %d\n", a, b);
    } else if (decoded_instruction == VERYSIMPLE_VM_IMUL) {
        int b = pop(state);
        int a = pop(state);
        push(state, a * b);
        log("imul %d %d\n", a, b);
    } else if (decoded_instruction == VERYSIMPLE_VM_LT) {
        int b = pop(state);
        int a = pop(state);
        push(state, a < b);
        log("lt %d %d\n", a, b);
    } else if (decoded_instruction == VERYSIMPLE_VM_GT) {
        int b = pop(state);
        int a = pop(state);
        push(state, a > b);
        log("gt %d %d\n", a, b);
    } else if (decoded_instruction == VERYSIMPLE_VM_EQ) {
        int b = pop(state);
        int a = pop(state);
        push(state, a == b);
        log("eq %d %d\n", a, b);
    } else if (decoded_instruction == VERYSIMPLE_VM_NEQ) {
        int b = pop(state);
        int a = pop(state);
        push(state, a != b);
        log("neq %d %d\n", a, b);
    } else if (decoded_instruction == VERYSIMPLE_VM_BRT) {
        int location = state->instructions[state->program_counter++];
        int flag = pop(state);
        log("brt %d %d\n", flag, location);
        if (flag) {
            state->program_counter = location;
        }
    } else if (decoded_instruction == VERYSIMPLE_VM_BRF) {
        int location = state->instructions[state->program_counter++];
        int flag = pop(state);
        log("brf %d %d\n", flag, location);
        if (!flag) {
            state->program_counter = location;
        }
    } else if (decoded_instruction == VERYSIMPLE_VM_CALL) {
        int location = state->instructions[state->program_counter++];
        int nargs = state->instructions[state->program_counter++];
        log("call %d %d\n", location, nargs);
        push(state, nargs);
        push(state, state->frame_pointer);
        push(state, state->program_counter);
        state->frame_pointer = state->stack_pointer;
        state->program_counter = location;
    } else if (decoded_instruction == VERYSIMPLE_VM_RET) {
        int function_return = pop(state);
        state->stack_pointer = state->frame_pointer;
        state->program_counter = pop(state);
        state->frame_pointer = pop(state);
        int nargs = pop(state);
        state->stack_pointer -= nargs;
        push(state, function_return);
        log("ret\n");
    } else if (decoded_instruction == VERYSIMPLE_VM_LOAD) {
        int offset = state->instructions[state->program_counter++];
        int val = state->stack[state->frame_pointer + offset];
        push(state, val);
        log("load %d = %d\n", offset, val);
    } else if (decoded_instruction == VERYSIMPLE_VM_STORE) {
        int val = pop(state);
        int offset = state->instructions[state->program_counter++];
        //TODO: put the val on stack/locals
        log("store %d = %d\n", offset, val);
    } else if (decoded_instruction == VERYSIMPLE_VM_PRINT) {
        log("print %d\n", peek(state));
    } else if (decoded_instruction == VERYSIMPLE_VM_HALT) {
        state->is_running = 0;
        log("halt\n");
    } else {
        log("Unknown instruction %d\n", decoded_instruction);
        ret_val = 0;
    }
    print_stack(state);
    return ret_val;
}

void run(int *instructions, int instructions_size, int entry_point) {
    int stack[100];
    struct vm_state state = {
            .stack = &stack,
            .stack_pointer = -1,
            .program_counter = entry_point,
            .instructions = instructions,
            .frame_pointer = -1,
            .is_running = 1
    };
    int is_execution_successful = 1;
    while (is_execution_successful && state.is_running && state.program_counter < instructions_size) {
        int instruction = fetch(&state);
        int decoded_instruction = decode(instruction);
        is_execution_successful = execute(&state, decoded_instruction);
    }
    return;
}
