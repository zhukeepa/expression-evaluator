#ifndef MISCINLINES_H
#define MISCINLINES_H

#include "Typedefs.h"

namespace mpw
{
    //:_: put this somewhere else
    inline bool isnan(double x)
    {
        return (x != x);
    }

    namespace math_expression
    {
        inline bool isoperator(char c)
        {
            return (c == '+' || c == '-' || c == '*' || c == '%' || c == '^');
        }

        inline Number nan()
        {
            int   i = 0x7fffffff;
            return static_cast<double>(*(reinterpret_cast<float*>(&i)));
        }
    }
}

#endif
