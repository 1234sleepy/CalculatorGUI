#include "pch.h"


#include "../../include/calculators/TrigCalculator.hpp"

TrigCalculator::CalcResult TrigCalculator::evaluateExpression(std::string expression)
{
    std::string expr{ evaluateAllTrigFunctions(expression) };

    std::vector<std::string> postfix{ BasicCalculator::convertInfixToPostfix(expr) };

	return BasicCalculator::evaluatePostfixExpression(postfix);
}


std::string TrigCalculator::evaluateAllTrigFunctions(std::string expression)
{
    std::string result = expression ;
    std::string ds{ result };

    std::regex trigPattern(
        R"(\b(sin|cos|tan|csc|sec|cot|acot|asin|acos|atan)\s*\(([^\(\)]*)\))",
        std::regex::icase
    );


    std::smatch match;

    while(std::regex_search(result, match, trigPattern))
    {
        TrigCalculator::trigMatch tr{ match[1], match[2] };

        double val{ 0.0 };

        if (tr.argument == "P")
        {
            val = std::round(M_PI * 1000000.0) / 1000000.0;
        }
        else
        {
            val = BasicCalculator::evaluateExpression(tr.argument).value;
        }

        double value{ 0.0 };

        if (tr.fucnction == "sin")
        {
            value = std::sin(val);
        }
        else if (tr.fucnction == "cos")
        {
            value = std::cos(val);
        }
        else if (tr.fucnction == "tan")
        {
            value = std::tan(val);
        }
        else if (tr.fucnction == "csc")
        {
            value = 1.0 / std::sin(val);
        }
        else if (tr.fucnction == "sec")
        {
            value = 1.0 / std::cos(val);
        }
        else if (tr.fucnction == "cot")
        {
            value  = 1.0 / std::tan(val);
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