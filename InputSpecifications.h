/**
 *  When entering an expression to be parsed, the expression must meet the following
 *  specificiations:
 *    - Implicit multiplication is, as of now, disallowed.
 *    - All operators are left-associative.
 *    - Functions, must be entered in the form f[x], rather than f(x).
 *
 *  Hence, the following are valid expressions:
 *    -  3 + 6 - 6 * 4
 *    -  3*sin[x]/44
 *    - tan[x]*(cos[x] + 4*x)
 *
 *  The term "value name" in this code refers to either the name of a variable
 *  or a constant value (e.g., pi,86.4).
*/
