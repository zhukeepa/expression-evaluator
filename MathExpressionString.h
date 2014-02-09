/**
  * THIS IS A PRIVATE FILE. NO RESULTS ARE GUARENTEED IF YOU #INCLUDE THIS FILE INTO
  * YOUR OTHER PIECES OF CODE. This is the declaration of a nested class; putting
  * its declaration in the header of the original class would make the original
  * class's private section too difficult to read. To top things off, it had two
  * nested classes, so I've decided to #include the code instead.
 */

class MathExpressionString : public String
{
public:
    //Overload the constructors!
    MathExpressionString()                        : String()     {}
    MathExpressionString(const std::string& str)  : String(str)  {}
    MathExpressionString(const char* s, size_t n) : String(s, n) {}
    MathExpressionString(const char* s)           : String(s)    {}
    MathExpressionString(size_t n, char c)        : String(n, c) {}
    MathExpressionString(const String& str, size_t pos, size_t n = npos)
        : String(str, pos, n) {}

    template<typename InputIterator> MathExpressionString(InputIterator begin, InputIterator end)
        : String (begin, end) {}

    MathExpressionString(const MathExpressionString& str)
        { *this = str.c_str(); }

    //"Value name"; this is so it encompasses both variables and constants.
    bool isValName() const;

    unsigned findValNameEnd  (unsigned) const;
    unsigned findValNameStart(unsigned) const;

    EvaluationTreeNode* getEvaluationTree();

private:
    void                replaceWithInverse     (char, char, String);
    void                changeOperationsToFuncs(unsigned char);
    void                juxtToOperation        (String);


    EvaluationTreeNode* parsePureMathExpression() const;
};
