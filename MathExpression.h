#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Globals.h"
#include "Functions.h"
#include "String.h"

#include <string>
#include <vector>

namespace mpw {
namespace math_expression {

class MathExpression
{
    /**
     * @brief This class represents a mathematical expression.
     *
     *  Its only real data member is the string representing that mathematical
     *  expression.
     */

private:
    class EvaluationTreeNode;
    class MathExpressionString;

public:
    MathExpression(MathExpressionString aExpr)
        : expressionUpdated(false), operations(0), mathExprStr(aExpr) {}

    void setExpr(String aExpr) { mathExprStr = aExpr; expressionUpdated = true; }
    MathExpression& operator= (String str) { setExpr(str); return *this; }

    String substitute(StrNumberMap const&);

private:
    #include "EvaluationTreeNode.h"
    #include "MathExpressionString.h"

    bool expressionUpdated;
    EvaluationTreeNode* operations;

    MathExpressionString mathExprStr;
};

} //mpw::math_expression
} //mpw

#endif
