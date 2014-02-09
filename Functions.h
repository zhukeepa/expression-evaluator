#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "Typedefs.h"
#include <list>

namespace mpw {
namespace math_expression {

Number negative  (std::list<Number> const&);
Number reciprocal(std::list<Number> const&);

Number add       (std::list<Number> const&);
Number multiply  (std::list<Number> const&);
Number mod       (std::list<Number> const&);
Number pow       (std::list<Number> const&);

Number sin       (std::list<Number> const&);
Number cos       (std::list<Number> const&);
Number tan       (std::list<Number> const&);
Number arcsin    (std::list<Number> const&);
Number arccos    (std::list<Number> const&);
Number arctan    (std::list<Number> const&);
Number arctan2   (std::list<Number> const&);

Number sinh      (std::list<Number> const&);
Number cosh      (std::list<Number> const&);
Number tanh      (std::list<Number> const&);

} //mpw::math_expression
} //mpw

#endif
