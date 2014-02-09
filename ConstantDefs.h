#ifndef CONSTANTDEFS_H
#define CONSTANTDEFS_H

#include <list>
#include <map>
#include <vector>
#include "Typedefs.h"
#include "Abbreviations.h"

namespace mpw {
namespace math_expression {

class ConstantDefs
{
    /**
     *  Some of the global variables are vectors and maps. Such global variables
     *  therefore need functions to define. Since the only way we may execute a function
     *  before main() is by calling a constructor, we call a constructor. This class
     *  is supposed to be hidden from user use; we therefore prefix every variable
     *  name and the class name with an underscore.
    */

public:
    std::vector< std::list<char> > _tierList; //Operation tiers; see documentation.
    ConstantDefs();
};

const ConstantDefs _constantDefs;

} //mpw::math_expression
} //mpw

#endif
