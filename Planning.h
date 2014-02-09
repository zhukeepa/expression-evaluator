/*
    ParentMathExpression
        - Has forms:
            - Scalar expression.
                - Real numbers
                    - Arbitrarily precise.
                    - Estimate.
                    - Exact (using expressions).
                - Complex numbers
                    - Ordered pair of reals.
                        - Both arbitrarily precise.
                        - Both estimates.
                        - Both exact (using expressions).
            - Matrix/vector expression.
                - Entries of real numbers.
                    - All arbitrary precision.
                    - All estimates.
                    - All exact (using expressions).
                - Entries of complex numbers.
                    - All arbitrarily precise.
                    - All estimates.
                    - All exact (using expressions).

            - If it is of one form, it must be entirely of that form. For example, if it
              contains a single sqrt(2) in it, (i.e., the expression is exact), all the
              terms will be exact, i.e., no rounding. Similarly, if there's any rounding,
              then no term is to be exact.
            - All expressions must have only type of rounding at a time.

            - Expressions are either constant or non-constant.
            - To evaluate a constant expression, go through the tree and evaluate.
                - Evaluation takes one argument, which specifies how to represent the
                  number (i.e., whether to make it arbitrarily precise or to use an
                  estimate).
            - In a non-constant expression:
                - If the expression is exact:
                    - If the substituted expression is exact, substitute the expression
                      and do simplify() (simple stuff).
                    - One can make the expression rounded simply by evaluationg every
                      "exact" term.
                    - If the substituted expression is rounded, round-ify the expression
                      and pass in the substituted terms.
                - If the expression is rounded:
                    - If the input is exact, round it, substitute, evaluate.
                    - If the input is rounded, substitute, evaluate.


        - Expression has a state in which it is forced to be scalar.
          This is to ensure that all terms of a matrix are scalar.

        - Can count # of variables.
*/


