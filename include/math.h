#ifndef VERYSIMPLE_VM_MATH_H
#define VERYSIMPLE_VM_MATH_H

/*All the op's are performed relative to second operand i.e, (b op a)*/


int iadd(int a, int b);

int isub(int a, int b);

int imul(int a, int b);

/**
 * Returns true if b < a
 * @param a
 * @param b
 * @return b < a
 */
int ilt(int a, int b);

/**
 * Returns true if b > a
 * @param a
 * @param b
 * @return
 */
int igt(int a, int b);

int ieq(int a, int b);

int ineq(int a, int b);

/**
 * Returns a. Acts as multiplicative identity
 * @param a
 * @return
 */
int identity(int a);

/**
 * Performs a !a
 * @param a
 * @return
 */
int negate_as_binary(int a);

#endif //VERYSIMPLE_VM_MATH_H
