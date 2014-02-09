#include "ConstantDefs.h"
#include "Abbreviations.h"
#include "Functions.h"
#include <cmath>

namespace mpw {
namespace math_expression {

ConstantDefs::ConstantDefs()
{
    //Define _tierList
    std::list<char> buf;
    buf.push_back('+');
    _tierList.push_back(buf);

    buf.clear();
    buf.push_back('*');
    buf.push_back('%');
    _tierList.push_back(buf);

    buf.clear();
    buf.push_back('^');
    _tierList.push_back(buf);
}

} //mpw::math_expression
} //mpw
