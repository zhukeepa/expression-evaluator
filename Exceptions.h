#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>

#define MAKE_CHILD_EXCEPTION_CLASS(name, parentName) \
class name : public parentName \
{ \
public: \
    name (std::string errMsg, std::string fileName, unsigned lineNo) : \
        parentName(errMsg, fileName, lineNo) {} \
}

namespace mpw {

class Exception
{
public:
    std::string what()        const { return errMsg_; }
    std::string getFileName() const { return fileName_; }
    unsigned getLineNo()      const { return lineNo_; }

    Exception(std::string errMsg,
              std::string fileName,
              unsigned lineNo) :
              errMsg_(errMsg), fileName_(fileName), lineNo_(lineNo) {}

protected:
    std::string errMsg_;     //Error message.
    std::string fileName_;   //File in which error occurred.
    unsigned    lineNo_;     //Line on which error occurred.
};

MAKE_CHILD_EXCEPTION_CLASS(StringError, Exception);
    MAKE_CHILD_EXCEPTION_CLASS(MissingClosingChar, StringError);
    MAKE_CHILD_EXCEPTION_CLASS(MissingStartingChar, StringError);

namespace math_expression {

MAKE_CHILD_EXCEPTION_CLASS(ArgumentError, Exception);
    MAKE_CHILD_EXCEPTION_CLASS(ArityError, ArgumentError);
    MAKE_CHILD_EXCEPTION_CLASS(MissingArgument, ArgumentError);

MAKE_CHILD_EXCEPTION_CLASS(InvalidMathExpression, Exception);
    MAKE_CHILD_EXCEPTION_CLASS(SyntaxError, InvalidMathExpression);
        MAKE_CHILD_EXCEPTION_CLASS(BadVarName, SyntaxError);
        MAKE_CHILD_EXCEPTION_CLASS(EmptyExpression, SyntaxError);
        MAKE_CHILD_EXCEPTION_CLASS(InvalidFunc, SyntaxError);
        MAKE_CHILD_EXCEPTION_CLASS(MissingOpeningParenthesis, SyntaxError);
        MAKE_CHILD_EXCEPTION_CLASS(MissingClosingParenthesis, SyntaxError);
        MAKE_CHILD_EXCEPTION_CLASS(StrayDecimal, SyntaxError);

    MAKE_CHILD_EXCEPTION_CLASS(IndeterminateValue, InvalidMathExpression);
        MAKE_CHILD_EXCEPTION_CLASS(DivisionByZero, IndeterminateValue);
        MAKE_CHILD_EXCEPTION_CLASS(ModuloByZero, IndeterminateValue);
        MAKE_CHILD_EXCEPTION_CLASS(ZeroToTheZeroth, IndeterminateValue);

}  //mpw::math_expression
}  //mpw



#endif
