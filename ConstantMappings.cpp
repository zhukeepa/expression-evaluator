#include "ConstantMappings.h"
#include "Typedefs.h"
#include "Abbreviations.h"
#include "MiscInlines.h"
#include "Functions.h"
#include "String.h"

namespace mpw {
namespace math_expression {

String getOpFuncName(char op)
{
    switch (op)
    {
        case '+': return "add";      break;
        case '*': return "multiply"; break;
        case '%': return "mod";      break;
        case '^': return "pow";      break;

        default : return "";
    }
}

PtrToMathFunc getFuncAddress(String str)
{
    if (str == "negative")   return &negative;
    if (str == "reciprocal") return &reciprocal;

    if (str == "add")        return &add;
    if (str == "multiply")   return &multiply;
    if (str == "mod")        return &mod;
    if (str == "pow")        return &pow;

    if (str == "sin")        return &sin;
    if (str == "cos")        return &cos;
    if (str == "tan")        return &tan;
    if (str == "arcsin")     return &arcsin;
    if (str == "arccos")     return &arccos;
    if (str == "arctan")     return &arctan;
    if (str == "arctan2")    return &arctan2;

    if (str == "sinh")       return &sinh;
    if (str == "cosh")       return &cosh;
    if (str == "tanh")       return &tanh;

    return 0;
}

Number getConstValue(String str)
{
    if (str == "pi") return 3.1415926535897932384626433832795;
    if (str == "e")  return 2.7182818284590452353602874713527;

    return nan();
}

} //mpw::math_expression
} //mpw
