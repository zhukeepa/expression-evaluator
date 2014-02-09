#ifndef ENUMERATIONS_H
#define ENUMERATIONS_H

namespace mpw {
namespace math_expression {

enum NodeState
{
    STATE_VAR,
    STATE_CONST,
    STATE_FUNC,
};

enum PrecisionState
{
    STATE_EXACT,
    STATE_ESTIMATE,
    STATE_ARBITRARY_PRECISION
};

} //mpw::math_expression
} //mpw

#endif
