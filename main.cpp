#include <iostream>
#include "String.h"
#include "Globals.h"
#include <string>
#include <utility>
#include <cmath>
#include <exception>
#include <queue>
#include "MathExpression.h"

using namespace std;
using namespace mpw;
using namespace math_expression;

int main()
{
    cout << "Your functions should be in terms of x. \n\n";

    while (true)
    {
        try
        {
            // sorry; never really learned how to correct this.
            fflush(stdin);

            std::cout << "Enter in your expression: ";
            std::string expression;
            std::cin >> expression;

            // sorry; never really learned how to correct this.
            fflush(stdin);

            long double val;
            std::cout << "Enter in your value. ";
            std::cin >> val;

            StrNumberMap foo;
            foo["x"] = val;

            MathExpression blah(expression);
            std::cout << blah.substitute(foo) << endl;
        }
        catch (Exception const& e)
        {
            std::cout << e.what() << endl;
            std::cout << e.getLineNo() << endl;
            std::cout << e.getFileName() << endl;
        }
        catch (exception const& e)
        {
            std::cout << e.what() << endl;
            std::cout << "STANDARD EXCEPTION";
        }
    }
}
