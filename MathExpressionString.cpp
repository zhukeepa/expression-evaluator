#include "Globals.h"
#include "MathExpression.h"

#include "String.h"
#include <sstream>

namespace mpw {
namespace math_expression {

bool
MathExpression::MathExpressionString::isValName() const
{
    /**
     *  @brief Checks to see if the string passed in meets the requirements of a
     *         variable or constant's name as specified in the documentation.
    */

    //Can't have no length.
    if (length() == 0)
        return false;

    //Can't start with a digit.
    if (isdigit((*this)[0]))
        return false;

    //Check to see if there are any non-letters or non-digits in the string.
    for (unsigned i = 1; i < length(); ++i)
    {
        if (!isalpha((*this)[i]) && !isdigit((*this)[i]))
            return false;
    }

    //If it passed all the above tests, this returns true.
    return true;
}

unsigned
MathExpression::MathExpressionString::findValNameEnd(unsigned start) const
{
    /**
     *  Given the location of the start of a mathematical expression, this function
     *  find the expression's end. Usually, expression's end is denoted by another
     *  operation (+, -, *, /, %, or ^) or the end of the string. However, if the
     *  expression contains an opening parenthesis or an opening bracket, note we
     *  we must jump to the closing parenthesis/bracket (because there may be an
     *  irrelevant operation within that parenthesis/bracket).
     *
     * For instance, consider the string 3*x
    */

    assert(start < size());
    //This actually has to be an expression.
    if (!isdigit((*this)[start]) && !isalpha((*this)[start]) &&
        (*this)[start] != '.' && (*this)[start] != '(')
        THROW_EXCEPTION(SyntaxError, "");

    unsigned index = start;
    while (index < size())
    {
        //:_:TODO:_: rearrange order; same as below
        if ((*this)[index] == '(')
            index = findClosingChar(index, ')');
        else if ((*this)[index] == '[')
            index = findClosingChar(index, ']');
        else if (isoperator((*this)[index]) || (*this)[index] == ','
            || (*this)[index] == ')' || (*this)[index] == ']')
            return index - 1;

        ++index;
    }

    return size() - 1;
}

unsigned
MathExpression::MathExpressionString::findValNameStart(unsigned end) const
{
    /**
     *  Same as findSubExprEnd(), except for two changes:
     *    a) We search backwards, not forward.
     *    b) if we encounter a closing bracket/parenthesis, IT MUST BE THE FIRST
     *       CHARACTER. Otherwise, it would be the result of, say, sin[x]y, where
     *       y is the first character (note that we're going in reverse; first in this
     *       sense is last in the usual sense), which is a syntax error. Furthermore,
     *       if it's a bracket, as brackets represent functions, we must search
     *       further for the start of the function name. We hence make a recursive
     *       function call to do this.
     *
     *       :_:TODO:_: Document this function.
    */

    assert(end < this->size());

    //This actually has to be an expression.
    if (!isdigit((*this)[end]) && !isalpha((*this)[end]) && (*this)[end] != '.' &&
        (*this)[end] != ')' && (*this)[end] != ']')
        THROW_EXCEPTION(SyntaxError, "");

    unsigned index = end;

    while (index != static_cast<unsigned>(-1))   //index >= 0 is always true; this is what we need.
    {
        if ((*this)[index] == ')')
            index = this->findOpeningChar(index, '(');
        else if ((*this)[index] == ']')
            index = this->findOpeningChar(index, '[') - 1;
        else if (isoperator((*this)[index]) || (*this)[index] == ',' ||
                 (*this)[index] == '(' || (*this)[index] == '[')
            return index + 1;

        --index;
    }

    return 0;
}

void
MathExpression::MathExpressionString::juxtToOperation(String op)
{
    /**
     * There are __ cases of implicit multiplication:
     *   Case 1: )value; for instance, (123)5 or (pi)e.
     *   Case 2: )(; for intance (123)(456).
     *   Case 3: )[; for instance, (13)[1, 2, 3].
     *   Case 4: ]value; for instance, [1, 2, 3]5.
     *   Case 5: ](; for instance, [1, 2, 3](pi).
     *   Case 6: number (; for instance, 123(asdfg) would become 123*asdfg.
     *   Case 7: number [; for instance, 123[3, 5, 5] would become 123*[3, 5, 5].
     *   Case 8: value [; for instance, pi[1, 2, 3] would become pi*[1, 2, 3].
     *   Case 9: number value; for instance, 3x or 3pi or 64asdfg123sdrdf (they would
     *           get turned into 3*x, 3*pi, and 64*asdfg123sdrdf).
     *   Case 10: value number; for instance, x.5 or 6x0.43 (they would get turned
     *            into x * 0.5 and 6*x0*.43*0.43; note that the decimal point is
     *            crucial).
     * Note that value ( is excluded; this is interpreted as a function.
    */

    MathExpressionString newMathExpressionString = "";
    newMathExpressionString += (*this)[0];

    //This part is to take care of cases 1, 2, 3, 4, 5, 6, 7, and 8.
    for (unsigned i = 1; i != this->length(); ++i)
    {
        char currentChar = (*this)[i];
        newMathExpressionString += currentChar;

        //Cases 1, 2, 3, 4, and 5 are covered here.
        if (currentChar == ')' || currentChar == ']')
        {
            //If we're at the last character, since implicit multiplication cannot
            //occur at ) or ] if they're the last character, we're done.
            if (i == this->length() - 1)
                continue;

            //Safe, since i is not the last character.
            char nextChar = (*this)[i + 1];

            //Normal syntax.
            if (isoperator(nextChar) || nextChar == ')' || nextChar == ']')
                continue;

            //See documentation to understand why this works.
            newMathExpressionString += op;
        }
        else if (currentChar == '(' || currentChar == '[')
        {
            //Safe, since i is not the last character.
            char prevChar = (*this)[i - 1];

            if (isoperator(prevChar) || prevChar == '(' || prevChar == '[')
                continue;

            //See documentation to understand why this works. Also, the extra if
            //statement is there to prevent turning a function, e.g., sin(x), into
            //sin*(x).
            if (currentChar != '(' || !isalpha(prevChar))
                newMathExpressionString.insert(newMathExpressionString.length() - 1, op);
        }
    }

    *this = newMathExpressionString;

    //Now, we complete case 9.
    unsigned i = 0;
    while (i < this->length())
    {
        char currentChar = (*this)[i];
        if (isdigit(currentChar) || currentChar == '.')
        {
            bool reachedStringEnd = false;
            do
            {
                if (i == this->length() - 1)
                {
                    reachedStringEnd = true;
                    break;
                }

                ++i;
                currentChar = (*this)[i];
            }
            while (isdigit(currentChar) || currentChar == '.');

            if (reachedStringEnd)
                break;

            if (isalpha(currentChar))
            {
                this->insert(i, op);
                do
                {
                    if (i == this->length() - 1)
                    {
                        reachedStringEnd = true;
                        break;
                    }

                    ++i;
                    currentChar = (*this)[i];
                }
                while (isalpha(currentChar) || isdigit(currentChar));

                if (currentChar == '.')
                {
                    this->insert(i, op);
                    const char* debug = c_str();

                    if (i == this->length() - 1)
                        THROW_EXCEPTION(StrayDecimal, "");

                    ++i;
                }
            }
        }
        else
            ++i;
    }

    //Case 10.
    i = 0;
    while (i < this->length())
    {
        char currentChar = (*this)[i];
        if (isalpha(currentChar))
        {
            bool reachedStringEnd = false;
            do
            {
                if (i == this->length() - 1)
                {
                    reachedStringEnd = true;
                    break;
                }

                ++i;
                currentChar = (*this)[i];
            }
            while (isalpha(currentChar) || isdigit(currentChar));

            if (reachedStringEnd)
                break;

            if (currentChar == '.')
            {
                if (i == this->size() - 1)
                    THROW_EXCEPTION(StrayDecimal, "");

                this->insert(i, op);
                ++i;
            }
        }
        else
            ++i;
    }
}

MathExpression::EvaluationTreeNode*
MathExpression::MathExpressionString::getEvaluationTree()
{
    //First, get rid of all of the spaces.
    this->removeChar(' ');

    //Explicitly add the * symbols in the implicit multiplication.
    this->juxtToOperation("*");

    //Replace all the -'s and /'s with their inverses.
    this->replaceWithInverse('+', '-', "negative");
    this->replaceWithInverse('*', '/', "reciprocal");

    //Replace all operations with functions.
    for (unsigned char i = tierList.size() - 1; i != static_cast<unsigned char>(-1); --i)
        this->changeOperationsToFuncs(i);

    //We now have the pure expression. We parse that one.
    MathExpression::EvaluationTreeNode* parsedMathExpression = this->parsePureMathExpression();

    //Simplify the tree and return it.
    parsedMathExpression->simplify();

    return parsedMathExpression;
}

void
MathExpression::MathExpressionString::replaceWithInverse(char op, //Short for operator.
                                                         char inverseOp,
                                                         String inverseFuncName)
{
    /**
     *  This method changes, say, 5 + 3 - 4 - 6 + 7 to 5 + 3 + negative(4) +
     *  negative(6) + 7.
    */

    unsigned index = 0;
    while ((index = this->find(inverseOp, index)) != String::npos)
    {
        //index can't be the last character; that's a syntax error.
        if (index == this->size() - 1)
            THROW_EXCEPTION(SyntaxError, "");

        unsigned exprEndLoc = this->findValNameEnd(index + 1);
        String buf = this->strBetweenIncl(index + 1, exprEndLoc);
        this->eraseBetweenIncl(index, exprEndLoc);
        this->insert(index, String(1, op) + inverseFuncName + String("(") +
                     buf + String(")"));
    }
}



void
MathExpression::MathExpressionString::changeOperationsToFuncs(unsigned char opTier)
{
    /**
     *  See documentation for information.
    */

    //opTier tells us which tier of operations we're trying to parse. We assert here
    //that there are no occurrences of any operation of a higher tier here (not
    //explicitly.) We also explicitly assert that opTier is in the range of possible
    //tiers of operations that can be parsed.
    assert(opTier < tierList.size());

    //If the string is one character long, there's no operation to parse.
    if (this->length() == 1)
        return;

    //Start at one and end at mathExprStr.size() - 2 because the first and last characters
    //can't be operations. If they are, we'll throw an exception sometime later in
    //the parsing process.
    for (std::list<char>::const_iterator it = tierList[opTier].begin();
         it != tierList[opTier].end(); ++it)
    {
        unsigned i = 0;
        while ((i = this->find(*it)) != String::npos)
        {
            //Split it up into the operand before and the operand after, and put
            //it together to get the corresponding function.
            unsigned preOperandMathExpressionStart = this->findValNameStart(i - 1);
            unsigned postOperandMathExpressionEnd  = this->findValNameEnd(i + 1);

            String preOperandMathExpression  = this->strBetweenIncl(preOperandMathExpressionStart,
                                                                    i - 1);
            String postOperandMathExpression = this->strBetweenIncl(i + 1,
                                                                    postOperandMathExpressionEnd);

            this->eraseBetweenIncl(preOperandMathExpressionStart,
                                   postOperandMathExpressionEnd);

            this->insert(preOperandMathExpressionStart, getOpFuncName(*it) +
                                                        String("(") +
                                                        preOperandMathExpression +
                                                        String(",") +
                                                        postOperandMathExpression +
                                                        String(")"));
        }
    }
}

MathExpression::EvaluationTreeNode*
MathExpression::MathExpressionString::parsePureMathExpression() const
{
    /**
     *  We have five cases:
     *    1. Something wrapped entirely within parentheses: in this case, we simply
     *       take the expression out of the parentheses and parse it.
     *    2. A function; this is easily verifiable, and we act accordingly.
     *    3. A syntax error: This happens if it's none of the above two cases and
     *       and there's a character that's neither digit, letter, or period.
     *    4. A constant Number: this is easily verifiable.
     *    3. A variable name: this only occurs if none of the above cases occur.
    */

    if (this->empty())
        THROW_EXCEPTION(SyntaxError, "Empty string");

    //Parentheses case
    if (this->isInParentheses())
    {
        return MathExpression::MathExpressionString(this->substr(1,
            this->size() - 2)).parsePureMathExpression();
    }

    if ((*this)[this->length() - 1] == ')')
    {
        //Find the opening bracket.
        unsigned openParenthLoc = this->find('(');
        if (openParenthLoc == String::npos)
            THROW_EXCEPTION(SyntaxError, "");

        std::map<char, char> symbolList;
        symbolList['['] = ']';
        symbolList['('] = ')';

        //Get the list of arguments.
        String argList = this->strBetweenIncl(openParenthLoc + 1, this->size() - 2); //list of arguments separated by commas
        std::list<String> subMathExpressionsToParse = argList.separateByCharEx(',', symbolList);

        //Get the function's name.
        String funcName = this->strBetweenIncl(0, openParenthLoc - 1);

        //Create the EvaluationTreeNode to return with that function address.
        MathExpression::EvaluationTreeNode* parsedEvaluationTreeNode =
            new MathExpression::EvaluationTreeNode(getFuncAddress(funcName));

        //Make sure the function is valid.
        if (parsedEvaluationTreeNode->func == 0)
            THROW_EXCEPTION(InvalidFunc, "");

        //Add the nodes to the tree and return it.
        for (std::list<String>::iterator it = subMathExpressionsToParse.begin();
             it != subMathExpressionsToParse.end(); ++it)
            parsedEvaluationTreeNode->addNode(MathExpression::MathExpressionString(*it).parsePureMathExpression());

        return parsedEvaluationTreeNode;
    }

    //If it's a number, treat it as such.
    if (this->isDouble())
        return new MathExpression::EvaluationTreeNode(this->toDouble());

    //If it's a variable, treat it as such.
    if (this->isValName())
    {
        //If it's a constant, treat it as such.
        Number constValue = getConstValue(*this);
        if (!isnan(constValue)) //True iff mathExprStr is the string representation of a constant, e.g., pi.
            return new MathExpression::EvaluationTreeNode(constValue);
        else
            return new MathExpression::EvaluationTreeNode(*this);
    }

    //If it's none of the above, it's a syntax error.
    THROW_EXCEPTION(SyntaxError, "");
}

} //mpw::math_expression
} //mpw
