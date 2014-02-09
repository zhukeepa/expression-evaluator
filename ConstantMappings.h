#ifndef CONSTANTMAPPINGS_H
#define CONSTANTMAPPINGS_H

#include "Abbreviations.h"
#include "Typedefs.h"

namespace mpw {
namespace math_expression {

String        getOpFuncName (char);
PtrToMathFunc getFuncAddress(String);
Number        getConstValue (String);

} //mpw::math_expression
} //mpw

#endif
