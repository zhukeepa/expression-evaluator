#include "MathExpression.h"
#include "Exceptions.h"
#include "Globals.h"
#include "String.h"

#include <sstream>
#include <cmath>

namespace mpw {
namespace math_expression {

MathExpression::EvaluationTreeNode::EvaluationTreeNode(PtrToMathFunc ptrToMathFunc)
{
    nodeState = STATE_FUNC;
    func = ptrToMathFunc;
}

MathExpression::EvaluationTreeNode::EvaluationTreeNode(Number x)
    : value(x), nodeState(STATE_CONST)
{
}

MathExpression::EvaluationTreeNode::EvaluationTreeNode(String str)
    : varName(str), nodeState(STATE_VAR)
{
}

MathExpression::EvaluationTreeNode::~EvaluationTreeNode()
{
    if (nodeState != STATE_FUNC)
        return;

    //Free the data in the node list, and free the data in all the children's
    //node lists.
    for (std::list<MathExpression::EvaluationTreeNode*>::iterator it = childNodes.begin();
         it != childNodes.end(); ++it)
        delete *it;
}

void MathExpression::EvaluationTreeNode::addNode(MathExpression::EvaluationTreeNode* newNode)
{
    if (nodeState == STATE_FUNC)
        childNodes.push_back(newNode);
    else
        assert("false"); //This should never happen.
}

String
MathExpression::EvaluationTreeNode::toString() //const
{
    switch (nodeState)
    {
        case STATE_CONST:
        {
            //:_:TODO:_: Un-const this function; why doesn't it work when this is
            //constant?
            std::ostringstream oss;
            oss << value;
            return oss.str();
        }
        break;

        case STATE_VAR:
            return varName;
        break;

        case STATE_FUNC:
        {
            String str;
            return str;
        }
        break;
    }

    //We should never reach here.
    assert(false);

    //Inaccessible code--this is to shut the compiler up when it warns that this
    //function does not return anything.
    return "";
}



MathExpression::EvaluationTreeNode*
MathExpression::EvaluationTreeNode::substitute(StrNumberMap const& varValues) const
{
    EvaluationTreeNode* substituted = subSubstitute(varValues);
    substituted->simplify();
    return substituted;
}



MathExpression::EvaluationTreeNode*
MathExpression::EvaluationTreeNode::subSubstitute(StrNumberMap const& varValues) const
{
    switch (nodeState)
    {
        case STATE_CONST:
            return new MathExpression::EvaluationTreeNode(*this);
        break;

        case STATE_VAR:
        {
            if (varValues.find(varName) != varValues.end())
            {
                MathExpression::EvaluationTreeNode* temp = new MathExpression::EvaluationTreeNode(varValues.find(varName)->second);
                return temp;
            }
            else
                return new MathExpression::EvaluationTreeNode(*this);
        }
        break;

        case STATE_FUNC:
        {
            std::list<MathExpression::EvaluationTreeNode*> substitutedChildNodes;
            for (std::list<MathExpression::EvaluationTreeNode*>::const_iterator it = childNodes.begin();
                 it != childNodes.end(); ++it)
                substitutedChildNodes.push_back((*it)->substitute(varValues));

            MathExpression::EvaluationTreeNode* substitutedEvaluationTreeNode = new MathExpression::EvaluationTreeNode(func);
            substitutedEvaluationTreeNode->childNodes = substitutedChildNodes;

            return substitutedEvaluationTreeNode;
        }
        break;
    }

    //We should never reach here.
    assert(false);

    //Inaccessible code--this is to shut the compiler up when it warns that this
    //function does not return anything.
    return new MathExpression::EvaluationTreeNode(0.0);
}

void
MathExpression::EvaluationTreeNode::groupAssociativeOperation(PtrToMathFunc op)
{
    if (nodeState == STATE_FUNC && func == op)
    {
        //Checks to see if any of the children nodes have that operation.
        //If so, add that child's nodes to the current node's own children,
        //and get rid of that child node. Repeat this until none of its child
        //nodes' functions are op. See the documentation of this function for
        //more information.
        for (std::list<MathExpression::EvaluationTreeNode*>::iterator it = childNodes.begin();
             it != childNodes.end(); ++it)
        {
            if ((*it)->nodeState == STATE_FUNC && (*it)->func == op)
            {
                childNodes.merge((*it)->childNodes);
                childNodes.erase(it);
                it = childNodes.begin();
            }
        }
    }
}

void
MathExpression::EvaluationTreeNode::evaluateFuncsOfConsts()
{
    if (nodeState != STATE_FUNC)
        return;

    //Check to see if all of the children are constants.
    std::list<Number> args;

    for (std::list<MathExpression::EvaluationTreeNode*>::iterator it = childNodes.begin();
         it != childNodes.end(); ++it)
    {
        if ((*it)->nodeState != STATE_CONST)
            break;
        else
            args.push_back((*it)->value);
    }

    //True iff every child is a constant.
    if (args.size() == childNodes.size())
    {
        Number valueBuf = (*func)(args);
        nodeState = STATE_CONST;
        value = valueBuf;
        return;
    }

    //Repeat this function for all the child nodes.
    for (std::list<MathExpression::EvaluationTreeNode*>::iterator it = childNodes.begin();
         it != childNodes.end(); ++it)
        (*it)->evaluateFuncsOfConsts();
}


void
MathExpression::EvaluationTreeNode::simplify()
{
    //First, group the associative operations together.
    groupAssociativeOperation(&add);
    groupAssociativeOperation(&multiply);

    //Next, remove any functions of constants that we come across (e.g., sin[8]).
    evaluateFuncsOfConsts();
}

} //mpw::math_expression
} //mpw
