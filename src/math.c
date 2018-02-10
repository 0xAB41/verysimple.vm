#include "../include/math.h"

int iadd(int a, int b) {
    return a + b;
}

int isub(int a, int b) {
    return b - a;
}

int imul(int a, int b) {
    return a * b;
}

int ilt(int a, int b) {
    return b < a;
}

int igt(int a, int b) {
    return !ilt(a, b);
}

int ieq(int a, int b) {
    return a == b;
}

int ineq(int a, int b) {
    return !ieq(a, b);
}

int identity(int a) {
    return a;
}

int negate_as_binary(int a) {
    return !a;
}