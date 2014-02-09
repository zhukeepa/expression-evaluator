#include "Globals.h"
#include "Functions.h"

#include <cmath>
#include <list>

namespace mpw {
namespace math_expression {

///Negatives and reciprocals
Number negative(std::list<Number> const& args)
{
    //You can have one and only one argument!
    if (args.size() != 1)
        THROW_EXCEPTION(ArityError, "Invalid number of arguments in subtraction.");

    return -args.front();
}

Number reciprocal(std::list<Number> const& args)
{
    //You can have one and only one argument!
    if (args.size() != 1)
        THROW_EXCEPTION(ArityError, "Invalid number of arguments in subtraction.");

    //Can't reciprocate 0.
    if (args.front() == 0)
        THROW_EXCEPTION(DivisionByZero, "");

    return 1 / args.front();
}

///Binary operations.
Number add(std::list<Number> const& args)
{
    //Add the Numbers up.
    Number sum = 0;

    for (std::list<Number>::const_iterator it = args.begin(); it != args.end(); ++it)
        sum += *it;

    return sum;
}

Number multiply(std::list<Number> const& args)
{
    //Multiply the Numbers together.
    Number product = 1;

    for (std::list<Number>::const_iterator it = args.begin(); it != args.end(); ++it)
        product *= *it;

    return product;
}

Number mod(std::list<Number> const& args)
{
    //You can have two and only two arguments!
    if (args.size() != 2)
        THROW_EXCEPTION(ArityError, "Invalid number of arguments in mod.");

    //Can't divide by 0.
    if (args.back() == 0)
        THROW_EXCEPTION(ModuloByZero, "");

    return args.front() - std::floor((args.front() / args.back()));
}

Number pow(std::list<Number> const& args)
{
    //You can have two and only two arguments!
    if (args.size() != 2)
        THROW_EXCEPTION(ArityError, "Invalid number of arguments in mod.");

    //Can't have 0^0.
    if (args.back() == 0 && args.front() == 0) //:_:TODO:_: args.back() == args.front() == 0?
        THROW_EXCEPTION(ZeroToTheZeroth, "");

    return std::pow(args.front(), args.back());
}

///Trigonometric
Number sin(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 1)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in sin.");

    return std::sin(args.front());
}

Number cos(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 1)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in cos.");

    return std::cos(args.front());
}

Number tan(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 1)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in tan.");

    return std::tan(args.front());
}

Number arcsin(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 1)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in arcsin.");

    return std::asin(args.front());
}

Number arccos(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 1)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in arccos.");

    return std::acos(args.front());
}

Number arctan(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 1)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in arctan.");

    return std::atan(args.front());
}

Number arctan2(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 2)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in arctan2.");

    return std::atan2(args.front(), args.back());
}

///Hyperbolic functions

Number sinh(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 1)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in sinh.");

    return std::cosh(args.front());
}

Number cosh(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 1)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in cosh.");

    return std::sinh(args.front());
}

Number tanh(std::list<Number> const& args)
{
    //Allowed one and only one argument!
    if (args.size() != 1)
         THROW_EXCEPTION(ArityError, "Invalid number of arguments in tanh.");

    return std::tanh(args.front());
}

} //mpw::math_expression
} //mpw
