#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <list>
#include <map>

#include "Abbreviations.h"
#include "ForwardDecls.h"

namespace mpw {
namespace math_expression {

typedef double Number;  //Type of the currently used numbers;
                        //long double here represents a real
                        //number. This may be changed to a complex
                        //number class later.

typedef Number(*PtrToMathFunc)(std::list<Number> const&);
typedef std::map<String, Number> StrNumberMap;
}
}

#endif
