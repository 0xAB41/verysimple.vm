#include <stdlib.h>
#include "../include/vsvm.h"
#include "../include/instruction_set.h"
#include "../include/logger.h"
#include "../include/math.h"

struct vm {
    int *instructions;
    int program_counter;
    int *stack;
    int stack_pointer;
    int frame_pointer;
    int is_running;
};

static void print_stack(struct vm *state) {
    log_debug("    [stack]");
    for (int i = 0; i <= state->stack_pointer; i++) {
        log_debug(" -> %d", state->stack[i]);
    }
    log_debug("\n");
}

static int pop(struct vm *state) {
    return state->stack[state->stack_pointer--];
}

static int push(struct vm *state, int value) {
    return (state->stack[++state->stack_pointer] = value) == value;
}

static int peek(struct vm *state) {
    return state->stack[state->stack_pointer];
}

static void save_state_and_jump_to_fn(struct vm *state) {
    int location = state->instructions[state->program_counter++];
    int nargs = state->instructions[state->program_counter++];
    log_debug("call %d %d\n", location, nargs);
    push(state, nargs);
    push(state, state->frame_pointer);
    push(state, state->program_counter);
    state->frame_pointer = state->stack_pointer;
    state->program_counter = location;
}

static void return_from_fn_and_unwind_stack(struct vm *state) {
    int function_return = pop(state);
    state->stack_pointer = state->frame_pointer;
    state->program_counter = pop(state);
    state->frame_pointer = pop(state);
    int nargs = pop(state);
    state->stack_pointer -= nargs;
    push(state, function_return);
    log_debug("ret\n");
}

static void perform_binary_op(struct vm *state, int (*op)(int, int), char *debug_str) {
    int a = pop(state);
    int b = pop(state);
    log_debug("%s %d %d\n", debug_str, a, b);
    push(state, op(a, b));
}

static void branch_on_condition(struct vm *state, int (*fn)(int), char *debug_str) {
    int location = state->instructions[state->program_counter++];
    int flag = pop(state);
    log_debug("%s %d %d\n", debug_str, flag, location);
    if (fn(flag)) {
        state->program_counter = location;
    }
}

static void load_const_rel_to_frame(struct vm *state) {
    int offset = state->instructions[state->program_counter++];
    int val = state->stack[state->frame_pointer + offset];
    push(state, val);
    log_debug("load %d = %d\n", offset, val);
}

static void load_const(struct vm *state) {
    int val = state->instructions[state->program_counter++];
    push(state, val);
    log_debug("iconst %d\n", val);
}

static int fetch(struct vm *state) {
    return state->instructions[state->program_counter++];
}

static int decode(int instruction) {
    return instruction;
}

static int execute(struct vm *state, int decoded_instruction) {
    int ret_val = 1;
    print_stack(state);
    switch (decoded_instruction) {
        case VERYSIMPLE_VM_ICONST:
            load_const(state);
            break;
        case VERYSIMPLE_VM_IADD:
            perform_binary_op(state, &iadd, "iadd");
            break;
        case VERYSIMPLE_VM_ISUB:
            perform_binary_op(state, &isub, "isub");
            break;
        case VERYSIMPLE_VM_IMUL:
            perform_binary_op(state, &imul, "imul");
            break;
        case VERYSIMPLE_VM_LT:
            perform_binary_op(state, &ilt, "lt");
            break;
        case VERYSIMPLE_VM_GT:
            perform_binary_op(state, &igt, "gt");
            break;
        case VERYSIMPLE_VM_EQ:
            perform_binary_op(state, &ieq, "eq");
            break;
        case VERYSIMPLE_VM_NEQ:
            perform_binary_op(state, &ineq, "neq");
            break;
        case VERYSIMPLE_VM_BRT:
            branch_on_condition(state, &identity, "brt");
            break;
        case VERYSIMPLE_VM_BRF:
            branch_on_condition(state, &negate_as_binary, "brf");
            break;
        case VERYSIMPLE_VM_CALL:
            save_state_and_jump_to_fn(state);
            break;
        case VERYSIMPLE_VM_RET:
            return_from_fn_and_unwind_stack(state);
            break;
        case VERYSIMPLE_VM_LOAD:
            load_const_rel_to_frame(state);
            break;
        case VERYSIMPLE_VM_PRINT:
            log_debug("print %d\n", peek(state));
            break;
        case VERYSIMPLE_VM_HALT:
            state->is_running = 0;
            log_debug("halt\n");
            break;
        default:
            log_error("Unknown instruction %d\n", decoded_instruction);
            ret_val = 0;
    }
    print_stack(state);
    return ret_val;
}

void run(int *instructions, int instructions_size, int entry_point) {
    int *stack = (int *) malloc(100 * sizeof(int));
    if (stack == NULL) {
        log_error("Could not allocate memory for stack\n");
        exit(1);
    }
    struct vm state = {
            .stack = stack,
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
    free(stack);
    return;
}