/**
  * THIS IS A PRIVATE FILE. NO RESULTS ARE GUARENTEED IF YOU #INCLUDE THIS FILE INTO
  * YOUR OTHER PIECES OF CODE. This is the declaration of a nested class; putting
  * its declaration in the header of the original class would make the original
  * class's private section too difficult to read. To top things off, it had two
  * nested classes, so I've decided to #include the code instead.
 */

class EvaluationTreeNode
{
public:
    ~EvaluationTreeNode();

    //:_:TODO:_: Privatize, make get/set functions for them.
    //:_:TODO:_: Err, make it a union?
    PtrToMathFunc func;
    std::list<EvaluationTreeNode*> childNodes;
    String varName;
    Number value;

    EvaluationTreeNode(PtrToMathFunc);
    EvaluationTreeNode(Number);
    EvaluationTreeNode(String);

    void addNode(EvaluationTreeNode*);
    String toString(); //:_:TODO:_:

    void simplify();
        void groupAssociativeOperation(PtrToMathFunc);
        void evaluateFuncsOfConsts();

    NodeState nodeState;

    EvaluationTreeNode* substitute(StrNumberMap const&) const;

private:
    EvaluationTreeNode* subSubstitute(StrNumberMap const&) const;
};
