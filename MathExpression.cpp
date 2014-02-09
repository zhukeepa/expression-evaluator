#include "MathExpression.h"
#include "Globals.h"
#include "String.h"
#include "ConstantMappings.h"
#include <queue>
#include <map>
#include <utility>
#include <list>
#include <iostream>

namespace mpw {
namespace math_expression {

String
MathExpression::substitute(StrNumberMap const& args)
{
    //Make sure your operations are present and up-to-date.
    if (operations == 0 || expressionUpdated)
    {
        expressionUpdated = false;
        operations = mathExprStr.getEvaluationTree();
    }

    return operations->substitute(args)->toString();
}

} //mpw::math_expression
} //mpw
