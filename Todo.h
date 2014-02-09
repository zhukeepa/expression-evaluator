/*
    DEGREES AND RADIANS

    Move isOperator.

    Implicit multiplication.

    Fix the const styles.

    Make sure that when users pass in their variables, the variable names don't overlap

    Separate the project into mpw (make a folder for that) and the expression
    parser itself. Also separate the files based on the namespaces they're in.

    Use a map for the function/consts, etc.?
        - Easier to check if there's an overlap with the name of a variable and a constant.
        - (Bimap?) To map a fuction's address to its name.
           - This would reqiure that there be a 1-1 correspondence between function
             names and addresses.

    - Other data types (e.g., vectors and matrices).
    - Extend functions.
    - Make a variable class including name and data type.

    - Make it recognize implicit multiplication and sin(x) rather than sin[x].
      - To make it recognize implicit multiplication, simply take a variable name;
        if it starts with a number, then make it into implicit multiplication.
      - In other cases, do parentheses replacements and parentheses checks, e.g.,
        replace )something or )( with )*something and )*(, respectively.

    - For functions, make a stack version that returns numbers, not strings.
    - Make optimizations (e.g., make -x + -y = -(x + y)).
    - Make optimal substitutions (sin(sin(x)) + sin(x) = z + sin(z), z = sin(x)).
    - Make a version that doesn't use lists or data type-checking for an increase in
      performance, as well as some with macros.

    Check out the online free graphing calculator thing.

    Wordsearch:
        Failed assertions saved to file logs?
        Remove multimap; simply use your own sort.

    Code::Blocks
        Somehow put hyperlinks into the code?

    with names of constants.

    If you have two threads, does one thread work slower than if there wer eonly one
    thread?
*/
