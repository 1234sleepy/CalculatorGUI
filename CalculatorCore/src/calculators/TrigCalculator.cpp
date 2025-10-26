#include "pch.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include "../../include/calculators/TrigCalculator.h"

#include <regex>
#include <string>
#include <sstream>


double TrigCalculator::evaluateExpression(const char expression[256])
{
	std::string expr = evaluateAllTrigFunctions(expression);

	std::vector<std::string> postfix = BasicCalculator::convertInfixToPostfix(expr);

	return BasicCalculator::evaluatePostfixExpression(postfix);
}


std::string TrigCalculator::evaluateAllTrigFunctions(const char expression[256])
{
    std::string result = expression;

    std::regex trigPattern(R"(\b(sin|cos|tan|asin|acos|atan)\s*\(([^()]*)\))", std::regex::icase);

    std::vector<std::smatch> matches
    {
        std::sregex_iterator(result.begin(), result.end(), trigPattern),
        std::sregex_iterator()
    };

    for (auto it = matches.rbegin(); it != matches.rend(); it++)
    {
        std::smatch match = *it;
        TrigCalculator::trigMatch tr = { match[1], match[2] };

        double val = 0.0;



        if (tr.argument == "P")
            val = std::round(M_PI * 1000000.0) / 1000000.0;
        else
            val = std::stod(tr.argument);

        double radians = val * M_PI / 180.0;
        double value = 0.0;

        if (tr.fucnction == "sin")
        {
            value = std::sin(radians);
        }
        else if (tr.fucnction == "cos")
        {
            value = std::cos(radians);
        }
        else if (tr.fucnction == "tan")
        {
            value = std::tan(radians);
        }
        else if (tr.fucnction == "cot")
        {
            value = value = 1.0 / std::tan(radians);
        }
        else if (val >= -1.0 && val <= 1.0)
        {
            if (tr.fucnction == "asin")
            {
                value = std::asin(val);
            }
            else if (tr.fucnction == "acos")
            {
                value = std::acos(val);
            }
            else if (tr.fucnction == "atan")
            {
                value = std::atan(val);
            }
            else if (tr.fucnction == "acot")
            {
                value = std::atan(1.0 / val);
            }
        }

        

        result.replace(match.position(), match.length(), std::to_string(value));
    }

    return result;
}